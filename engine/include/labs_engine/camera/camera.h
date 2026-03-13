#pragma once

#include <glm/ext/vector_float3.hpp>

#include <labs_engine/utils/types.h>

namespace leng
{
  class Camera
  {
    enum class Projection
    {
      Perspective,
      Orthographic
    };

   public:
    Camera(
      glm::vec3 const& position,
      glm::vec3 const& target,
      f32 fov = 90.f,
      f32 near = .01,
      f32 far = 100.f
    );
    Camera(
      glm::vec3 const& position,
      glm::vec3 const& target,
      f32 width = 800.f,
      f32 height = 600.f,
      f32 near = .01,
      f32 far = 100.f
    );

    ~Camera();

    auto position() const -> glm::vec3;
    auto target() const -> glm::vec3;
    auto fov() const -> f32;
    auto width() const -> f32;
    auto height() const -> f32;
    auto aspect() const -> f32;
    auto near() const -> f32;
    auto far() const -> f32;
    auto projection() const -> Projection;

    auto set_position(glm::vec3 const& position) -> void;
    auto set_target(glm::vec3 const& target) -> void;
    auto set_fov(f32 fov) -> void;
    auto set_width(f32 width) -> void;
    auto set_height(f32 height) -> void;
    auto set_aspect(f32 aspect) -> void;
    auto set_near(f32 near) -> void;
    auto set_far(f32 far) -> void;
    auto set_projection(Projection projection) -> void;

   private:
    Projection m_projection = Projection::Perspective;

    f32 m_fov = 90.f;
    f32 m_width = 800.f;
    f32 m_height = 600.f;
    f32 m_aspect = 1.f;
    f32 m_near = 0.01f;
    f32 m_far = 100.f;

    glm::vec3 m_position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 m_target = glm::vec3(0.f, 0.f, 0.f);
  };
}  // namespace leng
