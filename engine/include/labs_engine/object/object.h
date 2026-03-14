#pragma once

namespace leng
{
  class Object
  {
   public:
    Object();
    virtual ~Object();
    virtual auto tick(int const delta) -> void = 0;
  };
}  // namespace leng
