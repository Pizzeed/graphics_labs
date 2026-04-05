#pragma once
#include <deque>
#include <vector>
#include <memory>

#include <labs_engine/utils/types.h>
#include <labs_engine/object/object.h>
#include <labs_engine/object/render_object.h>

class IParticleEmitter
{
 public:
  struct Particle
  {
    std::shared_ptr<leng::RenderObject> body = nullptr;
    glm::vec3 velocity = {0, 0, 0};
    glm::vec3 spawn_pos = {0, 0, 0};
    f32 lifetime = 0;
    std::deque<std::shared_ptr<leng::RenderObject>> trail = {};
  };

  IParticleEmitter(
    std::shared_ptr<leng::RenderObject> const& particle_template
  );
  virtual ~IParticleEmitter();

  auto with_lifetime(f32 lifetime) -> IParticleEmitter&;
  auto with_interval(f32 interval) -> IParticleEmitter&;
  auto with_start_speed(f32 speed) -> IParticleEmitter&;
  auto with_trail_length(u32 trail) -> IParticleEmitter&;

  virtual auto start() -> void;
  virtual auto stop() -> void;
  virtual auto emit_particle() -> void = 0;

 protected:
  virtual auto tick_particles(f32 const delta) -> void;

  std::shared_ptr<leng::RenderObject> m_particle_template = nullptr;
  std::vector<Particle> m_particles = {};
  f32 m_particle_lifetime = 3;
  f32 m_interval = .5f;
  f32 m_current_interval = 0;
  f32 m_start_speed = 1.f;
  u32 m_trail_length = 4;

  bool m_running = false;
};
