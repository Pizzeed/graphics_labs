#include <labs_engine/glad/glad.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>
#include <labs_engine/mesh/objmesh.h>
#include <src/c++/cube.h>
#include <imgui.h>
#include <src/c++/bindings/imgui_impl_glfw.h>
#include <src/c++/bindings/imgui_impl_opengl3.h>

class UI : public leng::RenderObject
{
 public:
  UI(leng::OBJMesh* teapot)
    : m_teapot(teapot)
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(leng::Application::get()->window(), true);
    ImGui_ImplOpenGL3_Init("#version 420");
  }

  auto render(leng::Camera const& camera) -> void override
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    auto& io = ImGui::GetIO();
    ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin(
      "Overlay",
      nullptr,
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_AlwaysAutoResize
    );
    ImGui::SliderFloat("X Angle", &x_angle, 0, 360);
    ImGui::SliderFloat("Y Angle", &y_angle, 0, 360);
    ImGui::SliderFloat("Z Angle", &z_angle, 0, 360);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  auto tick(int const delta) -> void override
  {
    if(m_teapot) {
      m_teapot->set_rotation({x_angle, y_angle, z_angle});
    }
  }

 public:
  f32 x_angle = 0.f;
  f32 y_angle = 0.f;
  f32 z_angle = 0.f;

 private:
  leng::OBJMesh* m_teapot = nullptr;
};

int main()

{
  auto app = leng::Application::get()
               ->with_width(800)
               ->with_height(600)
               ->with_title("Test");
  app->init();
  auto material = leng::Material::from_files(
    std::string(CMAKE_BINARY_DIR)
      + "/assets/shaders/default_unlit/default_unlit.vert.glsl",
    std::string(CMAKE_BINARY_DIR)
      + "/assets/shaders/default_unlit/default_unlit.frag.glsl"

  );
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  auto teapot = leng::
    OBJMesh {std::string(CMAKE_BINARY_DIR) + "/assets/teapot.obj", material};
  auto ui = UI {&teapot};
  teapot.set_position({0.f, -2.f, -5.f});

  auto cube = Cube {material, 4};
  cube.set_position({3.f, -2.f, -5.f});

  app->current_camera().set_position(glm::vec3 {0.f, 0.f, 3.f});
  app->run_graphics_loop();
  return 0;
}
