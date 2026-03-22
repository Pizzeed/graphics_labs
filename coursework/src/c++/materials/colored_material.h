#pragma once

#include <labs_engine/glad/glad.h>
#include <labs_engine/material/material.h>
#include <labs_engine/utils/color.h>
#include <labs_engine/utils/types.h>
#include <glm/ext/vector_float3.hpp>

class ColoredMaterial : public leng::Material
{
 public:
  ColoredMaterial(
    std::string const& vertex_shader,
    std::string const& fragment_shader
  );

  static auto from_files(
    std::string const& vertex_shader_filename,
    std::string const& fragment_shader_filename
  ) -> ColoredMaterial;

  auto set_color(leng::Color const& color) -> void;
  auto set_light_position(glm::vec3 const& pos) -> void;
  auto set_light_color(glm::vec3 const& color) -> void;
  auto set_light_intensity(f32 intensity) -> void;

  auto use() const -> void override;

 private:
  leng::Color m_color;
  glm::vec3 m_light_pos;
  glm::vec3 m_light_color;
  f32 m_light_intensity;
};
