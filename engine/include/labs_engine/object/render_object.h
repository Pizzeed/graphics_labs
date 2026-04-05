#pragma once
#include <memory>

#include <glm/vec3.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/utils/transform.h>
#include <labs_engine/application/application.h>
#include <labs_engine/scene/scene.h>
#include <labs_engine/object/object.h>

namespace leng
{
  class RenderObject : public Object
  {
   public:
    RenderObject();
    virtual ~RenderObject();
    auto set_position(glm::vec3 const& position) -> void;
    auto set_scale(glm::vec3 const& scale) -> void;
    auto set_rotation(glm::vec3 const& rotation) -> void;
    auto set_transform(Transform const& transform) -> void;

    auto transform() const -> Transform const&;
    auto transform() -> Transform&;

   protected:
    virtual auto render(Camera const& camera) -> void = 0;

    Transform m_transform = {};

    // this is a crutch and i should probably rethink this
    struct GPUBuffer
    {
      u32 vao = 0;
      u32 vbo = 0;
      u32 ebo = 0;
    };

    std::shared_ptr<GPUBuffer> m_buffer = nullptr;

    friend void Scene::tick(f32);
  };
}  // namespace leng
