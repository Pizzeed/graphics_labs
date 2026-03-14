#pragma once

#include <labs_engine/material/material.h>
#include <labs_engine/mesh/mesh.h>

class Cube : public leng::Mesh
{
 public:
  Cube(leng::Material mat, int size = 3);

  auto tick(int const delta) -> void override;

 private:
  u32 m_size;
};
