#pragma once

#include <glm/ext/vector_float3.hpp>
#include <labs_engine/utils/types.h>

namespace leng
{
  class IParticleAttractor
  {
   public:
    virtual ~IParticleAttractor() = default;

    auto force() const -> f32 { return m_force; }

    auto range() const -> f32 { return m_range; }

    virtual auto closest_point(glm::vec3 const& to) const -> glm::vec3 = 0;

   private:
    f32 m_force = 0.5;
    f32 m_range = 1;
  };

}  // namespace leng
