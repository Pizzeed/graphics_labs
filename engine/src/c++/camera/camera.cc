#include <labs_engine/camera/camera.h>

namespace leng
{
  Camera::Camera(
    glm::vec3 const& position,
    glm::vec3 const& target,
    f32 fov,
    f32 near,
    f32 far
  )
    : m_position(position)
    , m_target(target)
    , m_fov(fov)
    , m_near(near)
    , m_far(far)
    , m_projection(Projection::Perspective)
  {}

  Camera::Camera(
    glm::vec3 const& position,
    glm::vec3 const& target,
    f32 width,
    f32 height,
    f32 near,
    f32 far
  )
    : m_position(position)
    , m_target(target)
    , m_width(width)
    , m_height(height)
    , m_near(near)
    , m_far(far)
    , m_projection(Projection::Orthographic)
  {}

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

  auto Camera::set_aspect(f32 aspect) -> void { m_aspect = aspect; }

  auto Camera::set_near(f32 near) -> void { m_near = near; }

  auto Camera::set_far(f32 far) -> void { m_far = far; }

  auto Camera::set_projection(Projection projection) -> void
  {
    m_projection = projection;
  }
}  // namespace leng
