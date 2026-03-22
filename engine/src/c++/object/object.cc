#include <labs_engine/object/object.h>
#include <labs_engine/scene/scene.h>
#include <labs_engine/application/application.h>

namespace leng
{
  Object::Object() {}

  Object::~Object() {}

  auto Object::destroy() -> void
  {
    if(not m_scene)
      return;
    m_scene->destroy_object(this);
  }
}  // namespace leng
