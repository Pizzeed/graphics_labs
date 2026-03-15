#include <string>
#include <iostream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <labs_engine/glad/glad.h>
#include <labs_engine/material/material.h>
#include <labs_engine/utils/types.h>

#include <src/c++/textured_material.h>

TexturedMaterial::TexturedMaterial(
  std::string const& vertex_shader,
  std::string const& fragment_shader
)
  : Material(vertex_shader, fragment_shader)
{}

TexturedMaterial::~TexturedMaterial() { glDeleteTextures(1, &m_texture); }

auto TexturedMaterial::from_files(
  std::string const& vertex_shader_filename,
  std::string const& fragment_shader_filename
) -> TexturedMaterial
{
  auto [v, f] = Material::
    load_files(vertex_shader_filename, fragment_shader_filename);
  return TexturedMaterial {v, f};
}

auto TexturedMaterial::set_texture(std::string const& filename) -> void
{
  if(not std::filesystem::exists(filename)) {
    std::cout << "File not found: " << filename << std::endl;
    return;
  }

  if(m_texture != 0)
    glDeleteTextures(1, &m_texture);

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER,
    GL_LINEAR_MIPMAP_LINEAR
  );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  auto data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
  if(data) {
    GLenum format;

    if(nrChannels == 1)
      format = GL_RED;
    else if(nrChannels == 3)
      format = GL_RGB;
    else if(nrChannels == 4)
      format = GL_RGBA;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      format,
      width,
      height,
      0,
      format,
      GL_UNSIGNED_BYTE,
      data
    );
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
}

auto TexturedMaterial::use() const -> void
{
  glBindTexture(GL_TEXTURE_2D, m_texture);
  Material::use();
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
}

auto TexturedMaterial::set_light_position(glm::vec3 const& pos) -> void
{
  m_light_pos = pos;
}

auto TexturedMaterial::set_light_color(glm::vec3 const& color) -> void
{
  m_light_color = color;
}
