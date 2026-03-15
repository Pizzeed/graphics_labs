#include <string>

#include <labs_engine/glad/glad.h>
#include <labs_engine/application/application.h>
#include <labs_engine/material/material.h>
#include <labs_engine/utils/types.h>

#include <src/c++/colored_material.h>

ColoredMaterial::ColoredMaterial(
  std::string const& vertex_shader,
  std::string const& fragment_shader
)
  : Material(vertex_shader, fragment_shader)
{}

auto ColoredMaterial::from_files(
  std::string const& vertex_shader_filename,
  std::string const& fragment_shader_filename
) -> ColoredMaterial
{
  auto [v, f] = Material::
    load_files(vertex_shader_filename, fragment_shader_filename);
  return ColoredMaterial {v, f};
}

auto ColoredMaterial::set_color(leng::Color const& color) -> void
{
  m_color = color;
}

auto ColoredMaterial::use() const -> void
{
  Material::use();
  glUniform4f(
    glGetUniformLocation(program(), "color"),
    (m_color.r() * 1.f) / 256.f,
    (m_color.g() * 1.f) / 256.f,
    (m_color.b() * 1.f) / 256.f,
    (m_color.a() * 1.f) / 256.f
  );
  glUniform3f(
    glGetUniformLocation(program(), "lightPos"),
    m_light_pos.x,
    m_light_pos.y,
    m_light_pos.z
  );
  glUniform3f(
    glGetUniformLocation(program(), "lightColor"),
    m_light_color.x,
    m_light_color.y,
    m_light_color.z
  );
  auto cam_pos = leng::Application::get()->current_camera().position();
  glUniform3f(
    glGetUniformLocation(program(), "viewPos"),
    cam_pos.x,
    cam_pos.y,
    cam_pos.z
  );
}

auto ColoredMaterial::set_light_position(glm::vec3 const& pos) -> void
{
  m_light_pos = pos;
}

auto ColoredMaterial::set_light_color(glm::vec3 const& color) -> void
{
  m_light_color = color;
}
