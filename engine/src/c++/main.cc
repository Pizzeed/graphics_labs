#include <labs_engine/application/application.h>

int main()
{
  auto app = leng::Application::get()
               ->with_width(1'280)
               ->with_height(720)
               ->with_title("Test");
  app->run_graphics_loop();
  return 0;
}
