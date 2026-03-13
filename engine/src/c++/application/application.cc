#include <chrono>
#include <iostream>
#include <chrono>

#include <labs_engine/glad/glad.h>

#include <GLFW/glfw3.h>

#include <labs_engine/utils/color.h>
#include <labs_engine/application/application.h>
#include <labs_engine/object/render_object.h>

namespace leng
{
  auto Application::framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
  ) -> void
  {
    Application* app = static_cast<Application*>(
      glfwGetWindowUserPointer(window)
    );
    app->m_window_width = width;
    app->m_window_height = height;
    glViewport(0, 0, width, height);
  }

  auto Application::get() -> Application*
  {
    static Application inst;
    return &inst;
  }

  Application::Application() {}

  Application::~Application() { cleanup(); }

  auto Application::init_graphics() -> void
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(
      m_window_width,
      m_window_height,
      m_window_title.c_str(),
      NULL,
      NULL
    );
    if(not m_window) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
    }
    glfwMakeContextCurrent(m_window);
    if(! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      return;
    }
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(
      m_window,
      &Application::framebuffer_size_callback
    );
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(
    //   [](
    //     GLenum source,
    //     GLenum type,
    //     GLuint id,
    //     GLenum severity,
    //     GLsizei length,
    //     GLchar const* message,
    //     void const* userParam
    //   ) { std::cout << "GL DEBUG: " << message << std::endl; },
    //   nullptr
    // );
  }

  auto Application::run_graphics_loop() -> void
  {
    using namespace std::chrono;

    auto last_time = steady_clock::now();

    while(not glfwWindowShouldClose(m_window)) {
      auto current_time = steady_clock::now();
      auto elapsed = duration_cast<seconds>(current_time - last_time);
      last_time = current_time;
      glClearColor(32.f / 255.f, 15.f / 255.f, 74.f / 255.f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      for(auto const& object : m_objects) {
        object->tick(elapsed.count());
        if(auto render = dynamic_cast<RenderObject*>(object.get()))
          render->render();
      }
      glfwPollEvents();
      glfwSwapBuffers(m_window);
    }
  }

  auto Application::cleanup() -> void
  {
    m_objects = {};
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  auto Application::window() -> GLFWwindow* const { return m_window; }

  auto Application::with_width(u32 const width) -> Application*
  {
    m_window_width = width;
    return this;
  }

  auto Application::with_height(u32 const height) -> Application*
  {
    m_window_height = height;
    return this;
  }

  auto Application::with_title(std::string const& title) -> Application*
  {
    m_window_title = title;
    return this;
  }

  auto Application::init() -> void { init_graphics(); }

  auto Application::add_object(std::shared_ptr<Object> const& object) -> void
  {
    if(not object)
      return;
    m_objects.push_back(object);
  }

  auto Application::remove_object(Object* object) -> void
  {
    if(not object)
      return;
    for(auto it = m_objects.begin(); it != m_objects.end(); ++it) {
      if(it->get() == object) {
        m_objects.erase(it);
        return;
      }
    }
  }
}  // namespace leng
