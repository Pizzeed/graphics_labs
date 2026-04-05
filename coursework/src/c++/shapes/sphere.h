#pragma once

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

class Sphere : public leng::Mesh
{
 public:
  Sphere(
    leng::Material* material,
    f32 radius = 1,
    u32 v_segments = 32,
    u32 h_segments = 32
  );
  virtual ~Sphere();

  virtual auto clone(bool on_scene = false)
    -> std::shared_ptr<leng::Object> override;

 protected:
  virtual auto tick(f32 const delta) -> void override {}

 private:
  f32 m_radius;
  u32 m_v_segments;
  u32 m_h_segments;
};
