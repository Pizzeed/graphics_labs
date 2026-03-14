#include <labs_engine/glad/glad.h>
#include <labs_engine/utils/types.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>

#include <src/c++/cube.h>

Cube::Cube(leng::Material mat, int size)
  : m_size(size)
  , leng::Mesh(mat)
{
  auto half = size / 2.0f;
  // clang-format off
  f32 vertices[] = {
  // x,     y,     z,     u,v,  nx, ny, nz
     0.5f, -0.5f, -0.5f,  0,0,   1,0,0,
     0.5f, -0.5f,  0.5f,  1,0,   1,0,0,
     0.5f,  0.5f,  0.5f,  1,1,   1,0,0,
     0.5f, -0.5f, -0.5f,  0,0,   1,0,0,
     0.5f,  0.5f,  0.5f,  1,1,   1,0,0,
     0.5f,  0.5f, -0.5f,  0,1,   1,0,0,

    -0.5f, -0.5f,  0.5f,  0,0,  -1,0,0,
    -0.5f, -0.5f, -0.5f,  1,0,  -1,0,0,
    -0.5f,  0.5f, -0.5f,  1,1,  -1,0,0,
    -0.5f, -0.5f,  0.5f,  0,0,  -1,0,0,
    -0.5f,  0.5f, -0.5f,  1,1,  -1,0,0,
    -0.5f,  0.5f,  0.5f,  0,1,  -1,0,0,

    -0.5f,  0.5f, -0.5f,  0,0,   0,1,0,
     0.5f,  0.5f, -0.5f,  1,0,   0,1,0,
     0.5f,  0.5f,  0.5f,  1,1,   0,1,0,
    -0.5f,  0.5f, -0.5f,  0,0,   0,1,0,
     0.5f,  0.5f,  0.5f,  1,1,   0,1,0,
    -0.5f,  0.5f,  0.5f,  0,1,   0,1,0,

    -0.5f, -0.5f,  0.5f,  0,0,   0,-1,0,
     0.5f, -0.5f,  0.5f,  1,0,   0,-1,0,
     0.5f, -0.5f, -0.5f,  1,1,   0,-1,0,
    -0.5f, -0.5f,  0.5f,  0,0,   0,-1,0,
     0.5f, -0.5f, -0.5f,  1,1,   0,-1,0,
    -0.5f, -0.5f, -0.5f,  0,1,   0,-1,0,

    -0.5f, -0.5f,  0.5f,  0,0,   0,0,1,
     0.5f, -0.5f,  0.5f,  1,0,   0,0,1,
     0.5f,  0.5f,  0.5f,  1,1,   0,0,1,
    -0.5f, -0.5f,  0.5f,  0,0,   0,0,1,
     0.5f,  0.5f,  0.5f,  1,1,   0,0,1,
    -0.5f,  0.5f,  0.5f,  0,1,   0,0,1,

     0.5f, -0.5f, -0.5f,  0,0,   0,0,-1,
    -0.5f, -0.5f, -0.5f,  1,0,   0,0,-1,
    -0.5f,  0.5f, -0.5f,  1,1,   0,0,-1,
     0.5f, -0.5f, -0.5f,  0,0,   0,0,-1,
    -0.5f,  0.5f, -0.5f,  1,1,   0,0,-1,
     0.5f,  0.5f, -0.5f,  0,1,   0,0,-1
    };

    int indices[6][4] = {
        {1, 5, 6, 2}, 
        {4, 0, 3, 7}, 
        {3, 2, 6, 7}, 
        {0, 1, 5, 4}, 
        {4, 5, 6, 7}, 
        {0, 1, 2, 3}  
    };

  // clang-format on

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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 8, 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(f32) * 8,
    (void*)(sizeof(f32) * 3)
  );
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(f32) * 8,
    (void*)(sizeof(f32) * 5)
  );
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  m_vertex_count = 8;
  m_index_count = 24;
}

auto Cube::tick(int const delta) -> void {}
