#pragma once

#include <glm/ext/vector_float3.hpp>

#include <labs_engine/glad/glad.h>
#include <labs_engine/material/material.h>
#include <labs_engine/utils/color.h>
#include <labs_engine/utils/types.h>

class TexturedMaterial : public leng::Material
{
 public:
  TexturedMaterial(
    std::string const& vertex_shader,
    std::string const& fragment_shader
  );

  ~TexturedMaterial();

  static auto from_files(
    std::string const& vertex_shader_filename,
    std::string const& fragment_shader_filename
  ) -> TexturedMaterial;

  auto set_texture(std::string const& filename) -> void;
  auto set_light_position(glm::vec3 const& pos) -> void;
  auto set_light_color(glm::vec3 const& color) -> void;
  auto set_light_intensity(f32 intensity) -> void;

  auto use() const -> void override;

 private:
  u32 m_texture = 0;
  glm::vec3 m_light_pos;
  glm::vec3 m_light_color;
  f32 m_light_intensity;
};
