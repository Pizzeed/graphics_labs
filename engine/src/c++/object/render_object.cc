#include <labs_engine/utils/types.h>
#include <labs_engine/object/render_object.h>

namespace leng
{
  RenderObject::RenderObject()
    : Object()
  {}

  RenderObject::~RenderObject() {}

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
