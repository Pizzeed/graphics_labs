#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <labs_engine/camera/camera.h>

namespace leng
{
  Camera::Camera() {}

  auto Camera::perspective(
    glm::vec3 const& position,
    glm::vec3 const& target,
    f32 fov,
    f32 width,
    f32 height,
    f32 near,
    f32 far
  ) -> Camera
  {
    auto cam = Camera {};
    cam.set_position(position);
    cam.set_target(target);
    cam.set_fov(fov);
    cam.set_width(width);
    cam.set_height(height);
    cam.set_near(near);
    cam.set_far(far);
    cam.set_projection(Projection::Perspective);
    return cam;
  }

  auto Camera::orthographic(
    glm::vec3 const& position,
    glm::vec3 const& target,
    f32 width,
    f32 height,
    f32 near,
    f32 far
  ) -> Camera
  {
    auto cam = Camera {};
    cam.set_position(position);
    cam.set_target(target);
    cam.set_width(width);
    cam.set_height(height);
    cam.set_near(near);
    cam.set_far(far);
    cam.set_projection(Projection::Orthographic);
    return cam;
  }

  Camera::~Camera() {}

  auto Camera::position() const -> glm::vec3 { return m_position; }

  auto Camera::target() const -> glm::vec3 { return m_target; }

  auto Camera::fov() const -> f32 { return m_fov; }

  auto Camera::width() const -> f32 { return m_width; }

  auto Camera::height() const -> f32 { return m_height; }

  auto Camera::aspect() const -> f32 { return m_width / m_height; }

  auto Camera::near() const -> f32 { return m_near; }

  auto Camera::far() const -> f32 { return m_far; }

  auto Camera::projection() const -> Projection { return m_projection; }

  auto Camera::set_position(glm::vec3 const& position) -> void
  {
    m_position = position;
  }

  auto Camera::set_target(glm::vec3 const& target) -> void
  {
    m_target = target;
  }

  auto Camera::set_fov(f32 fov) -> void { m_fov = fov; }

  auto Camera::set_width(f32 width) -> void { m_width = width; }

  auto Camera::set_height(f32 height) -> void { m_height = height; }

  auto Camera::set_near(f32 near) -> void { m_near = near; }

  auto Camera::set_far(f32 far) -> void { m_far = far; }

  auto Camera::set_projection(Projection projection) -> void
  {
    m_projection = projection;
  }

  auto Camera::view_matrix() const -> glm::mat4
  {
    return glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
  }

  auto Camera::projection_matrix() const -> glm::mat4
  {
    if(m_projection == Projection::Perspective)
      return glm::perspective(glm::radians(m_fov), aspect(), m_near, m_far);
    else
      return glm::ortho(-m_width, m_width, -m_height, m_height, m_near, m_far);
  }
}  // namespace leng
