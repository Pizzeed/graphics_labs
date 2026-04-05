#include <imgui.h>
#include <bindings/imgui_impl_glfw.h>
#include <bindings/imgui_impl_opengl3.h>

#include <labs_engine/glad/glad.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>
#include <labs_engine/utils/color.h>
#include <labs_engine/mesh/objmesh.h>

#include <materials/colored_material.h>
#include <materials/textured_material.h>
#include <shapes/sphere.h>
#include <shapes/tetrahedron_emitter.h>
#include <shapes/plane_attractor.h>
#include "particles/particle_attractor.h"
#include "particles/particle_emitter.h"

class UI : public leng::RenderObject
{
 public:
  UI(
    std::vector<leng::Material*> materials,
    Sphere* light_marker,
    IParticleEmitter* emitter,
    IParticleAttractor* attractor
  )
    : m_materials(materials)
    , m_light_marker(light_marker)
    , m_emitter(emitter)
    , m_attractor(attractor)
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
    ImGui::SliderFloat("Light X", &light_x, -100, 100);
    ImGui::SliderFloat("Light Y", &light_y, -100, 100);
    ImGui::SliderFloat("Light Z", &light_z, -100, 100);
    ImGui::SliderFloat("Light R", &light_r, 0, 1);
    ImGui::SliderFloat("Light G", &light_g, 0, 1);
    ImGui::SliderFloat("Light B", &light_b, 0, 1);
    ImGui::SliderFloat("Light Intensity", &light_int, 0, 1);
    ImGui::SliderFloat("Particle Lifetime", &lifetime, 0.1, 5);
    ImGui::SliderFloat("Particle Interval", &interval, 0.01, .5);
    ImGui::SliderFloat("Particle Speed", &speed, 0.1, 10);
    ImGui::SliderInt("Particle Trail", &trail, 0, 10);
    ImGui::SliderFloat("Attractor Force", &force, 0.1, 20);

    ImGui::Checkbox("Wireframe", &m_wireframe);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  auto tick(f32 const delta) -> void override
  {
    leng::Application::get()->current_scene()->current_camera().set_position(
      {camera_x_position, camera_y_position, camera_z_position}
    );
    leng::Application::get()->current_scene()->current_camera().set_target(
      {camera_x_target, camera_y_target, camera_z_target}
    );

    if(m_light_marker)
      m_light_marker->set_position({light_x, light_y, light_z});

    for(auto material : m_materials) {
      if(auto colmat = dynamic_cast<ColoredMaterial*>(material)) {
        colmat->set_light_position({light_x, light_y, light_z});
        colmat->set_light_color({light_r, light_g, light_b});
        colmat->set_light_intensity(light_int);
      }
      else if(auto texmat = dynamic_cast<TexturedMaterial*>(material)) {
        texmat->set_light_position({light_x, light_y, light_z});
        texmat->set_light_color({light_r, light_g, light_b});
        texmat->set_light_intensity(light_int);
      }
    }

    m_emitter->with_interval(interval)
      .with_lifetime(lifetime)
      .with_start_speed(speed)
      .with_trail_length(trail);

    m_attractor->set_force(force);

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

  auto clone(bool) -> std::shared_ptr<Object> override { return nullptr; }

 private:
  f32 camera_x_position = 0.f;
  f32 camera_y_position = 5.f;
  f32 camera_z_position = 5.f;
  f32 camera_x_target = 0.f;
  f32 camera_y_target = 0.f;
  f32 camera_z_target = 0.f;
  f32 light_x = 0.f;
  f32 light_y = 3.f;
  f32 light_z = 0.f;
  f32 light_r = 1.f;
  f32 light_g = 1.f;
  f32 light_b = 1.f;
  f32 light_int = .5f;
  f32 lifetime = 4.f;
  f32 interval = .01f;
  f32 speed = 5.f;
  int trail = 5;
  f32 force = 1.f;
  std::vector<leng::Material*> m_materials;
  Sphere* m_light_marker = nullptr;
  IParticleEmitter* m_emitter = nullptr;
  IParticleAttractor* m_attractor = nullptr;
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
  app->set_current_scene(std::make_shared<leng::Scene>());
  auto scene = app->current_scene();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto matte_mat = ColoredMaterial::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/matte/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/matte/frag.glsl"
  );
  auto black_mat = ColoredMaterial::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/matte/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/matte/frag.glsl"
  );
  auto unlit_mat = ColoredMaterial::from_files(
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/unlit/vert.glsl",
    std::string(CMAKE_BINARY_DIR) + "/assets/shaders/unlit/frag.glsl"
  );
  unlit_mat.set_color(leng::Color("#ffffff"));
  matte_mat.set_color(leng::Color::red());
  black_mat.set_color(leng::Color("#00000033"));
  auto light = scene->create_object<Sphere>(&unlit_mat, .2, 16, 16);

  auto emitter = scene->create_object<TetrahedronEmitter>(
    &matte_mat,
    std::make_shared<Sphere>(&black_mat, .1f, 16, 16),
    3.0f
  );

  auto plane = std::make_shared<Plane>(&matte_mat, 2.f);
  plane->set_position({3.f, 0.f, 0.f});
  scene->add_object(plane);

  emitter->add_attractor(plane);

  emitter->start();

  auto ui = scene->create_object<UI>(
    std::vector<leng::Material*> {&matte_mat, &black_mat},
    light.get(),
    emitter.get(),
    plane.get()
  );

  scene->current_camera().set_fov(90);
  app->run_graphics_loop();
  return 0;
}
