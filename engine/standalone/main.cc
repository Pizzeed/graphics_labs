#include <labs_engine/material/material.h>
#include <labs_engine/mesh/objmesh.h>
#include <labs_engine/application/application.h>

int main()
{
  auto app = leng::Application::get()
               ->with_width(800)
               ->with_height(600)
               ->with_title("Test");
  app->init();
  auto material = leng::Material::from_files(
    "./assets/shaders/default/default.vert.glsl",
    "./assets/shaders/default/default.frag.glsl"
  );
  auto teapot = leng::OBJMesh {"./assets/teapot.obj", material};
  app->run_graphics_loop();
  return 0;
}
