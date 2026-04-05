#pragma once

#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include <labs_engine/application/application.h>
#include <labs_engine/utils/types.h>
#include <labs_engine/camera/camera.h>

namespace leng
{
  class Object;

  class Scene
  {
   public:
    Scene();
    ~Scene();

    Scene(Scene const&) = delete;
    Scene(Scene&&) = delete;
    auto operator=(Scene const&) = delete;
    auto operator=(Scene&&) = delete;

    auto tick(f32 delta) -> void;

    auto current_camera() -> Camera&;
    auto set_current_camera(Camera const& camera) -> void;

    auto add_object(std::shared_ptr<Object> const& object) -> void;

    auto destroy_object(Object* object) -> void;

    template <ObjectDerived T, class... Args>
    auto create_object(Args&&... args) -> std::shared_ptr<T>;

   private:
    std::vector<std::shared_ptr<Object>> m_objects = {};
    std::vector<std::shared_ptr<Object>> m_added = {};
    std::vector<std::shared_ptr<Object>> m_removed = {};
    Camera m_current_camera;

    friend void Application::run_graphics_loop();
  };
}  // namespace leng

namespace leng
{

  template <ObjectDerived T, class... Args>
  auto Scene::create_object(Args&&... args) -> std::shared_ptr<T>
  {
    m_objects.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    m_objects.back()->m_scene = this;
    return static_pointer_cast<T>(m_objects.back());
  }
}  // namespace leng
