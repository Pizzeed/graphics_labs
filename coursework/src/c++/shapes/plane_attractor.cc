#include <glm/gtc/type_ptr.hpp>
#include "particles/particle_attractor.h"
#include <labs_engine/glad/glad.h>
#include <shapes/plane_attractor.h>

Plane::Plane(leng::Material* material, f32 size, f32 force, u32 range)
  : leng::Mesh(material)
  , m_size(size)
  , IParticleAttractor(force, range)
{
  struct Vertex
  {
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec3 normal;
  };

  f32 half = m_size * 0.5f;
  std::vector<Vertex> vertices = {
    // Front face (+X normal)
    {{0.f, -half, -half}, {0.f, 1.f}, {0.f, 1.f, 0.f}},
    {{0.f, half, -half}, {1.f, 1.f}, {0.f, 1.f, 0.f}},
    {{0.f, half, half}, {1.f, 0.f}, {0.f, 1.f, 0.f}},
    {{0.f, -half, half}, {0.f, 0.f}, {0.f, 1.f, 0.f}},

    // Back face (-X normal)
    {{0.f, -half, -half}, {0.f, 1.f}, {0.f, -1.f, 0.f}},
    {{0.f, half, -half}, {1.f, 1.f}, {0.f, -1.f, 0.f}},
    {{0.f, half, half}, {1.f, 0.f}, {0.f, -1.f, 0.f}},
    {{0.f, -half, half}, {0.f, 0.f}, {0.f, -1.f, 0.f}},
  };

  std::vector<u32> indices =
    {// Front face
     0,
     1,
     2,
     0,
     2,
     3,
     // Back face (reverse winding)
     6,
     5,
     4,
     7,
     6,
     4
    };

  glBindVertexArray(m_buffer->vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_buffer->vbo);
  glBufferData(
    GL_ARRAY_BUFFER,
    vertices.size() * sizeof(Vertex),
    vertices.data(),
    GL_STATIC_DRAW
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer->ebo);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(u32),
    indices.data(),
    GL_STATIC_DRAW
  );

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, pos)
  );

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, uv)
  );

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, normal)
  );

  glBindVertexArray(0);

  m_vertex_count = vertices.size();
  m_index_count = indices.size();
}

Plane::~Plane() {}

auto Plane::clone(bool on_scene) -> std::shared_ptr<leng::Object>
{
  auto obj = std::make_shared<Plane>(*this);
  if(on_scene && this->scene())
    this->scene()->add_object(obj);
  else
    obj->m_scene = nullptr;

  obj->m_model_loc = this->m_model_loc;
  obj->m_view_loc = this->m_view_loc;
  obj->m_proj_loc = this->m_proj_loc;

  return obj;
}

// Attractor: return closest point on plane (project particle onto plane)
auto Plane::closest_point(glm::vec3 const& to) const -> glm::vec3
{
  glm::vec3 plane_pos = this->transform().position;
  glm::vec3 plane_normal = this->transform().rotation
                         * glm::vec3 {0.f, 1.f, 0.f};
  f32 dist = glm::dot(to - plane_pos, plane_normal);
  glm::vec3 projected = to - plane_normal * dist;

  float half = m_size * 0.5f;
  projected.x = glm::clamp(projected.x, plane_pos.x - half, plane_pos.x + half);
  projected.z = glm::clamp(projected.z, plane_pos.z - half, plane_pos.z + half);
  projected.y = plane_pos.y;

  return projected;
}
