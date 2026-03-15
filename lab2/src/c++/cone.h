#pragma once

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

class Cone : public leng::Mesh
{
 public:
  Cone(
    leng::Material const& material,
    f32 radius = 1,
    f32 height = 1,
    u32 segments = 32
  );
  virtual ~Cone();

 protected:
  virtual auto tick(int const delta) -> void override {}

 private:
  f32 m_radius;
  f32 m_height;
  u32 m_segments;
};
