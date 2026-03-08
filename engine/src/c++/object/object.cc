#include <labs_engine/object/object.h>
#include <labs_engine/application/application.h>

namespace leng
{
  Object::Object()
  {
    Application::get()->add_object(std::shared_ptr<Object>(this));
  }

  Object::~Object() { Application::get()->remove_object(this); }
}  // namespace leng
