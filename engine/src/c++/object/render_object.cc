#include <labs_engine/glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <labs_engine/utils/types.h>
#include <labs_engine/object/render_object.h>

namespace leng
{
  RenderObject::RenderObject()
    : Object()
  {
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_ebo);
  }

  RenderObject::~RenderObject()
  {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
  }

  auto RenderObject::set_position(glm::vec3 const& position) -> void
  {
    m_transform.position = position;
  }

  auto RenderObject::set_scale(glm::vec3 const& scale) -> void
  {
    m_transform.scale = scale;
  }

  auto RenderObject::set_rotation(glm::vec3 const& rotation) -> void
  {
    m_transform.rotation = rotation;
  }

  auto RenderObject::set_transform(Transform const& transform) -> void
  {
    m_transform = transform;
  }
}  // namespace leng
