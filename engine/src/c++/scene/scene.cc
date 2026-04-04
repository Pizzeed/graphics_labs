#include <labs_engine/object/object.h>
#include <labs_engine/scene/scene.h>
#include <labs_engine/object/render_object.h>

namespace leng
{

  Scene::Scene()
    : m_current_camera(
        Camera::perspective({}, {}, 90.f, 800.f, 600.f, 0.01f, 1000.f)
      )
  {}

  Scene::~Scene() {}

  auto Scene::tick(int delta) -> void
  {
    for(auto const& object : m_objects) {
      object->tick(delta);
      if(auto render = dynamic_cast<RenderObject*>(object.get()))
        render->render(m_current_camera);
    }
  }

  auto Scene::current_camera() -> Camera& { return m_current_camera; }

  auto Scene::set_current_camera(Camera const& camera) -> void
  {
    m_current_camera = camera;
  }

  auto Scene::add_object(std::shared_ptr<Object> const& object) -> void
  {
    m_objects.push_back(object);
  }

  auto Scene::destroy_object(Object* object) -> void
  {
    for(auto it = m_objects.begin(); it != m_objects.end(); ++it) {
      if(it->get() == object) {
        m_objects.erase(it);
        return;
      }
    }
  }
}  // namespace leng
