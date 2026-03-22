#pragma once

#include <memory>

#include <labs_engine/object/render_object.h>
#include <labs_engine/utils/transform.h>
#include <labs_engine/utils/types.h>
#include <labs_engine/object/object.h>

class Particle : public leng::Object
{
 public:
  Particle(leng::RenderObject* body_template);

  ~Particle() = default;

  auto start() -> void;

 protected:
  virtual auto tick(int const delta) -> void override;
  virtual auto on_creation() -> void;
  virtual auto on_death() -> void;

 private:
  leng::Transform m_transform;
  std::unique_ptr<leng::RenderObject> m_body_template = nullptr;
  std::unique_ptr<leng::RenderObject> m_trail_template = nullptr;
  u32 m_trail_length = 0;
  u32 m_lifetime_sec = 0;
};
