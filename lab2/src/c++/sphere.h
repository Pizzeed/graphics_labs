#pragma once

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

class Sphere : public leng::Mesh
{
 public:
  Sphere(
    leng::Material const& material,
    f32 radius = 1,
    u32 v_segments = 32,
    u32 h_segments = 32
  );
  virtual ~Sphere();

 protected:
  virtual auto tick(int const delta) -> void override {}

 private:
  f32 m_radius;
  u32 m_v_segments;
  u32 m_h_segments;
};
