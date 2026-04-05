#pragma once

#include <random>

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

#include <particles/particle_emitter.h>

class TetrahedronEmitter : public leng::Mesh,
                           public IParticleEmitter
{
 public:
  TetrahedronEmitter(
    leng::Material* material,
    std::shared_ptr<RenderObject> const& particle_template,
    f32 size = 1
  );

  ~TetrahedronEmitter() override = default;

 protected:
  virtual auto tick(f32 const delta) -> void override;
  virtual auto clone(bool on_scene) -> std::shared_ptr<leng::Object> override;
  virtual auto render(leng::Camera const& camera) -> void override;
  virtual auto emit_particle() -> void override;

 private:
  auto get_random_point() -> std::pair<glm::vec3, glm::vec3>;

  f32 m_size = 1;
  std::vector<glm::vec3> m_vertices = {};
  std::vector<glm::vec3> m_real_vertices = {};
  bool m_real_vertices_dirty = false;
  std::vector<std::shared_ptr<IParticleAttractor>> m_attractors = {};
  std::mt19937 m_rng;
};
