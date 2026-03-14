#include <labs_engine/glad/glad.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>
#include <labs_engine/mesh/objmesh.h>
#include <src/c++/cube.h>

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
    OBJMesh {std::string(CMAKE_BINARY_DIR) + "./assets/teapot.obj", material};
  teapot.set_position({0.f, -2.f, -5.f});

  auto cube = Cube {material, 3};
  cube.set_position({0.f, -2.f, -5.f});

  app->current_camera().set_position(glm::vec3 {0.f, 0.f, 3.f});
  app->run_graphics_loop();
  return 0;
}
