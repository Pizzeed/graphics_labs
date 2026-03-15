#include <imgui.h>
#include <labs_engine/glad/glad.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>
#include <labs_engine/mesh/objmesh.h>

#include <src/c++/bindings/imgui_impl_glfw.h>
#include <src/c++/bindings/imgui_impl_opengl3.h>

#include <src/c++/cube.h>
#include <src/c++/sphere.h>
#include <src/c++/cone.h>

class UI : public leng::RenderObject
{
 public:
  UI(Sphere* s, Cone* c)
    : m_sphere(s)
    , m_cone(c)
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
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground
    );
    ImGui::SliderFloat("Camera X Position", &camera_x_position, -100, 100);
    ImGui::SliderFloat("Camera Y Position", &camera_y_position, -100, 100);
    ImGui::SliderFloat("Camera Z Position", &camera_z_position, -100, 100);
    ImGui::SliderFloat("Camera X Target", &camera_x_target, -100, 100);
    ImGui::SliderFloat("Camera Y Target", &camera_y_target, -100, 100);
    ImGui::SliderFloat("Camera Z Target", &camera_z_target, -100, 100);
    ImGui::Checkbox("Wireframe", &m_wireframe);
    ImGui::Checkbox("Task 4", &m_task4);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  auto tick(int const delta) -> void override
  {
    leng::Application::get()->current_camera().set_position(
      {camera_x_position, camera_y_position, camera_z_position}
    );
    leng::Application::get()->current_camera().set_target(
      {camera_x_target, camera_y_target, camera_z_target}
    );
    if(m_prev_wireframe != m_wireframe) {
      if(m_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
      m_prev_wireframe = m_wireframe;
    }

    if(m_prev_task4 != m_task4) {
      if(m_task4) {
        if(m_sphere)
          m_sphere->set_scale({1.5, 1.5, 1.5});
        if(m_cone)
          m_cone->set_position({5, -4, 0});
      }
      else {
        if(m_sphere)
          m_sphere->set_scale({1, 1, 1});
        if(m_cone)
          m_cone->set_position({5, -1, 0});
      }
      m_prev_task4 = m_task4;
    }
  }

 private:
  f32 camera_x_position = 0.f;
  f32 camera_y_position = 5.f;
  f32 camera_z_position = 5.f;
  f32 camera_x_target = 0.f;
  f32 camera_y_target = 0.f;
  f32 camera_z_target = 0.f;
  bool m_wireframe = false;
  bool m_prev_wireframe = false;
  bool m_task4 = false;
  bool m_prev_task4 = false;
  Sphere* m_sphere = nullptr;
  Cone* m_cone = nullptr;
};

int main()

{
  auto app = leng::Application::get()
               ->with_width(1'280)
               ->with_height(720)
               ->with_title("Test");
  app->init();
  auto unlit_material = leng::Material::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/default_unlit/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/default_unlit/frag.glsl"
  );
  auto lit_material = leng::Material::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/default_lit/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/default_lit/frag.glsl"
  );
  auto lit_untextured_material = leng::Material::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/lit_untextured/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/lit_untextured/frag.glsl"
  );
  auto test_material = leng::Material::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/test/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/test/frag.glsl"

  );

  auto teapot = leng::OBJMesh {
    std::string(CMAKE_BINARY_DIR) + "/assets/teapot.obj",
    unlit_material
  };
  teapot.set_position({0, -1, 0});
  teapot.set_rotation({30, 0, 0});
  auto cube = Cube {unlit_material, 4};
  auto sphere = Sphere {unlit_material, 1, 64, 64};
  auto cone = Cone {test_material, 1, 2, 64};

  sphere.set_position({5, 0, 0});
  cone.set_position({5, -1, 0});

  auto ui = UI {&sphere, &cone};

  app->current_camera().set_fov(90);
  app->run_graphics_loop();
  return 0;
}
