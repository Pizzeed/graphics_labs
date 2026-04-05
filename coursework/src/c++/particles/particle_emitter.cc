#include <algorithm>
#include <iostream>
#include <particles/particle_emitter.h>

IParticleEmitter::IParticleEmitter(
  std::shared_ptr<leng::RenderObject> const& particle_template
)
{
  if(particle_template)
    m_particle_template = particle_template;
}

IParticleEmitter::~IParticleEmitter() {}

auto IParticleEmitter::start() -> void
{
  m_running = true;
  m_current_interval = m_interval;
}

auto IParticleEmitter::stop() -> void { m_running = false; }

auto IParticleEmitter::tick_particles(f32 const delta) -> void
{
  if(m_running) {
    m_current_interval -= delta;
    if(m_current_interval <= 0) {
      emit_particle();
      m_current_interval = m_interval;
    }
  }

  for(auto& p : m_particles) {
    p.trail.push_back(
      static_pointer_cast<leng::RenderObject>(p.body->clone(true))
    );
    p.body->set_position(p.body->transform().position + p.velocity * delta);
    p.lifetime -= delta;
    if(p.lifetime <= 0) {
      p.body->scene()->destroy_object(p.body.get());
      for(auto const& trail : p.trail)
        trail->scene()->destroy_object(trail.get());
      p.trail.clear();
      continue;
    }
    if(p.trail.size() > m_trail_length && p.trail.size() > 0) {
      p.trail.front()->scene()->destroy_object(p.trail.front().get());
      p.trail.pop_front();
    }
  }

  auto it = std::remove_if(m_particles.begin(), m_particles.end(), [](auto& p) {
    return p.lifetime <= 0;
  });

  m_particles.erase(it, m_particles.end());
}

auto IParticleEmitter::with_lifetime(f32 lifetime) -> IParticleEmitter&
{
  m_particle_lifetime = lifetime;
  return *this;
}

auto IParticleEmitter::with_interval(f32 interval) -> IParticleEmitter&
{
  m_interval = interval;
  return *this;
}

auto IParticleEmitter::with_start_speed(f32 speed) -> IParticleEmitter&
{
  m_start_speed = speed;
  return *this;
}

auto IParticleEmitter::with_trail_length(u32 trail) -> IParticleEmitter&
{
  m_trail_length = trail;
  return *this;
}
