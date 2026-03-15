#include <labs_engine/glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/material/material.h>
#include "cone.h"

Cone::Cone(leng::Material const& material, f32 radius, f32 height, u32 segments)
  : leng::Mesh(material)
  , m_radius(radius)
  , m_segments(segments)
{
  auto vertices = std::vector<glm::vec3>();
  auto indices = std::vector<u32>();
  vertices.emplace_back(0, m_radius, 0);
  vertices.emplace_back(glm::vec3 {0, 0, 0});
  for(int i = 0; i <= m_segments; ++i) {
    auto angle = 2.f * std::numbers::pi_v<f32> * i / m_segments;
    auto cos_a = std::cos(angle);
    auto sin_a = std::sin(angle);
    auto x = cos_a * m_radius;
    auto z = sin_a * m_radius;
    vertices.emplace_back(x, 0, z);
  }

  for(int i = 0; i <= m_segments; ++i) {
    indices.emplace_back(0);
    indices.emplace_back(i + 1);
    indices.emplace_back(i + 2);

    indices.emplace_back(1);
    indices.emplace_back(i + 1);
    indices.emplace_back(i + 2);
  }

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(
    GL_ARRAY_BUFFER,
    vertices.size() * sizeof(glm::vec3),
    vertices.data(),
    GL_STATIC_DRAW
  );
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(u32),
    indices.data(),
    GL_STATIC_DRAW
  );

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  m_vertex_count = vertices.size();
  m_index_count = indices.size();
}

Cone::~Cone() {}
