#pragma once

#include <memory>

namespace leng
{
  class Object : public std::enable_shared_from_this<Object>
  {
   public:
    Object();
    virtual ~Object();
    virtual auto tick(int const delta) -> void = 0;
  };
}  // namespace leng
