#include <labs_engine/object/render_object.h>
#include <particles/particle.h>

Particle(leng::RenderObject* body_template, u32 lifetime_sec);

auto Particle::tick(int const delta) -> void
{
  if(not m_created)
    return;
  m_current_lifetime -= delta;
  if(m_lifetime_sec <= 0)
    die();
}

auto Particle::create() -> void
{
  m_created = true;
  m_body = m_body_template;
}

auto Particle::die() -> void {}
