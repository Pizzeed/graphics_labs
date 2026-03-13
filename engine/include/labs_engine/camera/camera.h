#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
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
    static auto perspective(
      glm::vec3 const& position,
      glm::vec3 const& target,
      f32 fov,
      f32 width,
      f32 height,
      f32 near,
      f32 far
    ) -> Camera;
    static auto orthographic(
      glm::vec3 const& position,
      glm::vec3 const& target,
      f32 width,
      f32 height,
      f32 near,
      f32 far
    ) -> Camera;

    ~Camera();

    auto view_matrix() const -> glm::mat4;
    auto projection_matrix() const -> glm::mat4;

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
    auto set_near(f32 near) -> void;
    auto set_far(f32 far) -> void;
    auto set_projection(Projection projection) -> void;

   private:
    Camera();
    Projection m_projection = Projection::Perspective;

    f32 m_fov;
    f32 m_width;
    f32 m_height;
    f32 m_near;
    f32 m_far;

    glm::vec3 m_position;
    glm::vec3 m_target;
  };
}  // namespace leng
