#pragma once

#include <glm/ext/vector_float3.hpp>
#include <labs_engine/utils/types.h>

class IParticleAttractor
{
 public:
  IParticleAttractor(f32 force = 0.5, f32 range = 1)
    : m_force(force)
    , m_range(range)
  {}

  virtual ~IParticleAttractor() = default;

  auto force() const -> f32 { return m_force; }

  auto range() const -> f32 { return m_range; }

  auto set_force(f32 force) -> void { m_force = force; }

  auto set_range(f32 range) -> void { m_range = range; }

  virtual auto closest_point(glm::vec3 const& to) const -> glm::vec3 = 0;

 protected:
  f32 m_force = 0.5;
  f32 m_range = 1;
};
