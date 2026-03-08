#pragma once

#include <memory>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#include <labs_engine/utils/types.h>
#include <labs_engine/object/render_object.h>

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
    auto window() -> GLFWwindow* const;
    auto run_graphics_loop() -> void;

   private:
    Application();
    auto init_graphics() -> void;
    auto add_object(std::shared_ptr<Object> const& object) -> void;
    auto remove_object(Object* object) -> void;
    auto cleanup() -> void;
    static auto framebuffer_size_callback(
      GLFWwindow* window,
      int width,
      int height
    ) -> void;

    friend class Object;
    std::vector<std::shared_ptr<Object>> m_objects = {};

    GLFWwindow* m_window;
    u32 m_window_width = 800;
    u32 m_window_height = 600;
    std::string m_window_title = "New Application";
  };
}  // namespace leng
