#pragma once

#include <memory>
#include <type_traits>

namespace leng
{
  class Scene;

  class Object
  {
   public:
    Object();
    virtual ~Object();
    virtual auto tick(int const delta) -> void = 0;
    virtual auto destroy() -> void;
    virtual auto clone(bool on_scene = false) -> std::shared_ptr<Object> = 0;

    auto scene() -> Scene*;

   private:
    Scene* m_scene = nullptr;

    friend class Scene;
  };

  template <class T>
  concept ObjectDerived = std::is_base_of_v<Object, T>;
}  // namespace leng
