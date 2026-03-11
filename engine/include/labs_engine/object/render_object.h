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
    virtual auto render() -> void = 0;

    Transform m_transform = {};
    u32 m_shader_program = -1;
    u32 m_vao = -1;
    u32 m_vbo = -1;
    u32 m_ebo = -1;

    friend void Application::run_graphics_loop();
  };
}  // namespace leng
