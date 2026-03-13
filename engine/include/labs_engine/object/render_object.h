#pragma once

#include <glm/vec3.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/utils/transform.h>
#include <labs_engine/application/application.h>
#include <labs_engine/object/object.h>

namespace leng
{
  class RenderObject : public Object
  {
   public:
    RenderObject();
    virtual ~RenderObject();
    auto set_position(glm::vec3 const& position) -> void;
    auto set_scale(glm::vec3 const& scale) -> void;
    auto set_rotation(glm::vec3 const& rotation) -> void;
    auto set_transform(Transform const& transform) -> void;

    auto transform() const -> Transform const&;
    auto transform() -> Transform&;

   protected:
    virtual auto render(Camera const& camera) -> void = 0;

    Transform m_transform = {};
    u32 m_vao = 0;
    u32 m_vbo = 0;
    u32 m_ebo = 0;

    friend void Application::run_graphics_loop();
  };
}  // namespace leng
