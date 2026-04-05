#include <labs_engine/object/object.h>
#include <labs_engine/scene/scene.h>
#include <labs_engine/object/render_object.h>
#include <algorithm>

namespace leng
{

  Scene::Scene()
    : m_current_camera(
        Camera::perspective({}, {}, 90.f, 800.f, 600.f, 0.01f, 1000.f)
      )
  {}

  Scene::~Scene() {}

  auto Scene::tick(f32 delta) -> void
  {
    auto removed = std::
      remove_if(m_objects.begin(), m_objects.end(), [this](auto const& object) {
        return std::find(m_removed.begin(), m_removed.end(), object)
            != m_removed.end();
      });

    m_objects.erase(removed, m_objects.end());
    m_objects.insert(m_objects.end(), m_added.begin(), m_added.end());

    m_added.clear();
    m_removed.clear();

    for(auto const& object : m_objects) {
      if(object)
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
    if(std::find(m_added.begin(), m_added.end(), object) != m_added.end())
      return;

    if(std::find(m_objects.begin(), m_objects.end(), object) != m_objects.end())
      return;

    if(
      std::find(m_removed.begin(), m_removed.end(), object) != m_removed.end()
    ) {
      m_removed.erase(
        std::remove(m_removed.begin(), m_removed.end(), object),
        m_removed.end()
      );
      object->m_scene = this;
    }
    else {
      m_added.push_back(object);
      object->m_scene = this;
    }
  }

  auto Scene::destroy_object(Object* ptr) -> void
  {
    if(not ptr)
      return;

    if(
      auto found = std::find_if(
        m_added.begin(),
        m_added.end(),
        [ptr](auto const& object) { return object.get() == ptr; }
      );
      found != m_added.end()
    ) {
      m_added.erase(found);
      (*found)->m_scene = nullptr;
    }

    if(
      auto found = std::find_if(
        m_removed.begin(),
        m_removed.end(),
        [ptr](auto const& object) { return object.get() == ptr; }
      );
      found != m_removed.end()
    )
      return;

    if(
      auto found = std::find_if(
        m_objects.begin(),
        m_objects.end(),
        [ptr](auto const& object) { return object.get() == ptr; }
      );
      found == m_objects.end()
    )
      return;
    else {
      m_removed.push_back(*found);
      (*found)->m_scene = nullptr;
    }
  }
}  // namespace leng
