#include <labs_engine/glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <labs_engine/utils/types.h>
#include <labs_engine/object/render_object.h>

namespace leng
{
  RenderObject::RenderObject()
  {
    m_buffer = std::make_unique<GPUBuffer>();
    glGenBuffers(1, &m_buffer->vbo);
    glGenVertexArrays(1, &m_buffer->vao);
    glGenBuffers(1, &m_buffer->ebo);
  }

  RenderObject::~RenderObject()
  {
    if(m_buffer.use_count() == 1) {
      glDeleteBuffers(1, &m_buffer->vbo);
      glDeleteVertexArrays(1, &m_buffer->vao);
      glDeleteBuffers(1, &m_buffer->ebo);
    }
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

  auto RenderObject::transform() const -> Transform const&
  {
    return m_transform;
  }

  auto RenderObject::transform() -> Transform& { return m_transform; }
}  // namespace leng
