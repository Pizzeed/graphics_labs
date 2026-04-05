#pragma once

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>
#include <particles/particle_attractor.h>

class Plane : public leng::Mesh,
              public IParticleAttractor
{
 public:
  Plane(leng::Material* material, f32 size, f32 force = 1.0f, u32 range = 5);
  virtual ~Plane();

  virtual auto clone(bool on_scene = false)
    -> std::shared_ptr<leng::Object> override;

  virtual auto closest_point(glm::vec3 const& to) const -> glm::vec3 override;

 protected:
  virtual auto tick(f32 const delta) -> void override {}

 private:
  f32 m_size;
};
