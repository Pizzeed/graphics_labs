#include <imgui.h>
#include <labs_engine/glad/glad.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>
#include <labs_engine/utils/color.h>

#include <bindings/imgui_impl_glfw.h>
#include <bindings/imgui_impl_opengl3.h>

#include <shapes/sphere.h>
#include <materials/colored_material.h>
#include <materials/textured_material.h>

class UI : public leng::RenderObject
{
 public:
  UI()
    : leng::RenderObject()
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
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  auto tick(int const delta) -> void override
  {
    leng::Application::get()->current_scene()->current_camera().set_position(
      {camera_x_position, camera_y_position, camera_z_position}
    );
    leng::Application::get()->current_scene()->current_camera().set_target(
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
};

int main()

{
  auto app = leng::Application::get()
               ->with_width(1'280)
               ->with_height(720)
               ->with_title("Test");
  app->init();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  app->current_scene()->current_camera().set_fov(90);
  app->run_graphics_loop();
  return 0;
}
