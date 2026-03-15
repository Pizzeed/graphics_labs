#include <labs_engine/glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/material/material.h>
#include "sphere.h"

Sphere::Sphere(
  leng::Material const& material,
  f32 radius,
  u32 v_segments,
  u32 h_segments
)
  : leng::Mesh(material)
  , m_radius(radius)
  , m_v_segments(v_segments)
  , m_h_segments(h_segments)
{
  struct Vertex
  {
    glm::vec3 position;
    glm::vec3 normal;
  };

  auto vertices = std::vector<Vertex>();
  auto indices = std::vector<u32>();
  auto seg_h = (m_radius * 2) / m_h_segments;
  vertices.emplace_back(glm::vec3 {0, m_radius, 0}, glm::vec3 {0, 1, 0});
  for(int i = m_v_segments * .5f - 1; i > m_v_segments * -.5f + 1; --i) {
    auto y = seg_h * i;
    auto layer_r = i == 0 ? m_radius : std::sqrt(m_radius * m_radius - y * y);
    for(int j = 0; j <= m_v_segments; ++j) {
      auto angle = 2.0f * std::numbers::pi_v<f32> * j / m_v_segments;
      auto cos_a = std::cos(angle);
      auto sin_a = std::sin(angle);
      auto x = cos_a * layer_r;
      auto z = sin_a * layer_r;
      glm::vec3 pos = {x, y, z};
      vertices.emplace_back(pos, pos / m_radius);
    }
  }
  vertices.emplace_back(glm::vec3 {0, -m_radius, 0}, glm::vec3 {0, -1, 0});

  auto ring_vertices = m_v_segments + 1;
  auto first_ring = 1;
  auto rings = (vertices.size() - 2) / ring_vertices;
  auto last_ring = first_ring + (rings - 1) * ring_vertices;
  auto bottom = vertices.size() - 1;

  for(u32 i = 0; i < m_v_segments; ++i) {
    indices.push_back(0);
    indices.push_back(first_ring + i);
    indices.push_back(first_ring + i + 1);
  }

  for(u32 ring = 0; ring < m_h_segments - 3; ++ring) {
    u32 current = first_ring + ring * ring_vertices;
    u32 next = current + ring_vertices;

    for(u32 i = 0; i < m_v_segments; ++i) {
      u32 a = current + i;
      u32 b = current + i + 1;
      u32 c = next + i;
      u32 d = next + i + 1;

      indices.push_back(a);
      indices.push_back(c);
      indices.push_back(b);

      indices.push_back(b);
      indices.push_back(c);
      indices.push_back(d);
    }
  }

  for(u32 i = 0; i < m_v_segments; ++i) {
    indices.push_back(last_ring + i);
    indices.push_back(last_ring + i + 1);
    indices.push_back(bottom);
  }

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(
    GL_ARRAY_BUFFER,
    vertices.size() * sizeof(Vertex),
    vertices.data(),
    GL_STATIC_DRAW
  );
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(u32),
    indices.data(),
    GL_STATIC_DRAW
  );

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)sizeof(glm::vec3)
  );
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  m_vertex_count = vertices.size();
  m_index_count = indices.size();
}

Sphere::~Sphere() {}
