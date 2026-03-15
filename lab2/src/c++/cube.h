#pragma once

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

class Cube : public leng::Mesh
{
 public:
  Cube(leng::Material const& material, int size = 3);
  virtual ~Cube();

 protected:
  virtual auto tick(int const delta) -> void override {}

 private:
  u32 m_size;
};
