#include <labs_engine/glad/glad.h>
#include <labs_engine/utils/types.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>

#include <cube.h>

Cube::Cube(leng::Material mat, int size)
  : m_size(size)
  , leng::Mesh(mat)
{
  // auto half = size * .5f;
  // // clang-format off
  // f32 vertices[] = {
  // // positions            uvs   normals
  //   -half, -half,  half,  0,0,  0,0,1,
  //    half, -half,  half,  1,0,  0,0,1,
  //    half,  half,  half,  1,1,  0,0,1,
  //   -half,  half,  half,  0,1,  0,0,1,

  //   -half, -half, -half,  1,0,  0,0,-1,
  //    half, -half, -half,  0,0,  0,0,-1,
  //    half,  half, -half,  0,1,  0,0,-1,
  //   -half,  half, -half,  1,1,  0,0,-1,

  //   -half, -half, -half,  0,0, -1,0,0,
  //   -half, -half,  half,  1,0, -1,0,0,
  //   -half,  half,  half,  1,1, -1,0,0,
  //   -half,  half, -half,  0,1, -1,0,0,

  //    half, -half, -half,  1,0,  1,0,0,
  //    half, -half,  half,  0,0,  1,0,0,
  //    half,  half,  half,  0,1,  1,0,0,
  //    half,  half, -half,  1,1,  1,0,0,

  //   -half,  half, -half,  0,0,  0,1,0,
  //    half,  half, -half,  1,0,  0,1,0,
  //    half,  half,  half,  1,1,  0,1,0,
  //   -half,  half,  half,  0,1,  0,1,0,

  //   -half, -half, -half,  0,0,  0,-1,0,
  //    half, -half, -half,  1,0,  0,-1,0,
  //    half, -half,  half,  1,1,  0,-1,0,
  //   -half, -half,  half,  0,1,  0,-1,0
  // };

  // u32 indices[] = {
  //     0, 1, 2,  0, 2, 3,
  //     4, 5, 6,  4, 6, 7,
  //     8, 9,10,  8,10,11,
  //    12,13,14, 12,14,15,
  //    16,17,18, 16,18,19,
  //    20,21,22, 20,22,23
  // };

  // clang-format off
  f32 vertices[] = {
    1.0, 1.0, 0.0, 
    0.0, 1.0, 0.0, 
    0.0, 0.0, 0.0, 
    1.0, 0.0, 0.0, 
  };

  // clang-format on
  u32 indices[] = {0, 1, 2, 0, 2, 3};
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    sizeof(indices),
    indices,
    GL_STATIC_DRAW
  );
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  // glVertexAttribPointer(
  //   1,
  //   2,
  //   GL_FLOAT,
  //   GL_FALSE,
  //   sizeof(f32) * 8,
  //   (void*)(sizeof(f32) * 3)
  // );
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(
  //   2,
  //   3,
  //   GL_FLOAT,
  //   GL_FALSE,
  //   sizeof(f32) * 8,
  //   (void*)(sizeof(f32) * 5)
  // );
  // glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  m_vertex_count = 4;
  m_index_count = 6;
}

Cube::~Cube() {}

auto Cube::tick(int const delta) -> void {}
