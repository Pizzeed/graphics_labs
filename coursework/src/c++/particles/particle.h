#pragma once

#include <memory>

#include <labs_engine/object/object.h>
#include <labs_engine/object/render_object.h>
#include <labs_engine/utils/transform.h>
#include <labs_engine/utils/types.h>

class Particle : public leng::Object
{
 public:
  Particle(leng::RenderObject* body_template, u32 lifetime_sec);

  ~Particle() = default;

 protected:
  virtual auto tick(int const delta) -> void override;
  virtual auto create() -> void;
  virtual auto die() -> void;

 private:
  bool m_created = false;
  leng::Transform m_transform;
  std::unique_ptr<leng::RenderObject> m_body_template = nullptr;
  std::unique_ptr<leng::RenderObject> m_body = nullptr;
  f32 m_lifetime_sec = 0;
  f32 m_current_lifetime = m_lifetime_sec;
};
