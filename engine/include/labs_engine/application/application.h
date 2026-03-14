#pragma once

#include <memory>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#include <labs_engine/utils/types.h>
#include <labs_engine/object/object.h>
#include <labs_engine/camera/camera.h>

namespace leng
{
  class Application
  {
   public:
    Application(Application const&) = delete;
    Application(Application&&) = delete;
    auto operator=(Application const&) = delete;
    auto operator=(Application&&) = delete;
    ~Application();

    static auto get() -> Application*;
    auto with_width(u32 const width) -> Application*;
    auto with_height(u32 const height) -> Application*;
    auto with_title(std::string const& title) -> Application*;
    auto init() -> void;
    auto run_graphics_loop() -> void;

    auto window() -> GLFWwindow* const;
    auto current_camera() -> Camera&;

    auto set_current_camera(Camera const& camera) -> void;

   private:
    Application();
    auto init_graphics() -> void;
    auto add_object(Object* object) -> void;
    auto remove_object(Object* object) -> void;
    auto cleanup() -> void;
    static auto framebuffer_size_callback(
      GLFWwindow* window,
      int width,
      int height
    ) -> void;

    friend class Object;

    std::vector<Object*> m_objects = {};

    GLFWwindow* m_window;
    u32 m_window_width = 800;
    u32 m_window_height = 600;
    std::string m_window_title = "New Application";

    Camera m_current_camera;
  };
}  // namespace leng
