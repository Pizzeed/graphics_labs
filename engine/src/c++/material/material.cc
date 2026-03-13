#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include <labs_engine/glad/glad.h>
#include <GLFW/glfw3.h>

#include <labs_engine/material/material.h>

namespace leng
{
  Material::Material(
    std::string const& vertex_shader,
    std::string const& fragment_shader
  )
    : m_v_src(vertex_shader)
    , m_f_src(fragment_shader)
  {
    compile_vertex();
    compile_fragment();
    compile_program();
  }

  Material::~Material()
  {
    glDeleteProgram(m_shader_program);
    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);
  }

  auto Material::from_files(
    std::string const& vertex_shader_filename,
    std::string const& fragment_shader_filename
  ) -> Material
  {
    if(not std::filesystem::exists(vertex_shader_filename)) {
      std::cout << "File not found: " << vertex_shader_filename << std::endl;
      return Material {"", ""};
    }
    if(not std::filesystem::exists(fragment_shader_filename)) {
      std::cout << "File not found: " << fragment_shader_filename << std::endl;
      return Material {"", ""};
    }
    std::stringstream v_ss, f_ss;
    std::ifstream file = {};
    std::cout << "Reading vertex shader from " << vertex_shader_filename
              << std::endl;
    file.open(vertex_shader_filename);
    v_ss << file.rdbuf();
    file.close();
    file.open(fragment_shader_filename);
    std::ifstream file2(fragment_shader_filename);
    std::cout << "Reading fragment shader from " << fragment_shader_filename
              << std::endl;
    f_ss << file2.rdbuf();
    file.close();
    return Material {v_ss.str(), f_ss.str()};
  }

  auto Material::is_valid() const -> bool
  {
    return m_v_compiled && m_f_compiled && m_program_compiled;
  }

  auto Material::program() const -> u32 { return m_shader_program; }

  auto Material::last_error() const -> std::string
  {
    if(m_last_error != nullptr)
      return "";
    return *m_last_error;
  }

  auto Material::vertex_error() const -> std::string { return m_vertex_error; }

  auto Material::fragment_error() const -> std::string
  {
    return m_fragment_error;
  }

  auto Material::program_error() const -> std::string
  {
    return m_program_error;
  }

  auto Material::compile_vertex() -> void
  {
    if(m_v_src == "") {
      m_v_compiled = false;
      return;
    }
    m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    auto dt = m_v_src.data();
    glShaderSource(m_vertex_shader, 1, &dt, nullptr);
    glCompileShader(m_vertex_shader);

    int success;
    char infoLog[512];
    glGetShaderiv(m_vertex_shader, GL_COMPILE_STATUS, &success);

    if(success) {
      m_v_compiled = true;
      return;
    }
    glGetShaderInfoLog(m_vertex_shader, 512, nullptr, infoLog);
    m_vertex_error = infoLog;
    m_last_error = &m_vertex_error;
    m_v_compiled = false;
    std::cout << "Vertex shader compilation error: " << infoLog << std::endl;
    return;
  }

  auto Material::compile_fragment() -> void
  {
    if(m_f_src == "") {
      m_f_compiled = false;
      return;
    }
    m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    auto dt = m_f_src.data();
    glShaderSource(m_fragment_shader, 1, &dt, nullptr);
    glCompileShader(m_fragment_shader);

    int success;
    glGetShaderiv(m_fragment_shader, GL_COMPILE_STATUS, &success);

    if(success) {
      m_f_compiled = true;
      return;
    }
    char infoLog[512];
    glGetShaderInfoLog(m_fragment_shader, 512, nullptr, infoLog);
    m_fragment_error = infoLog;
    m_last_error = &m_fragment_error;
    m_f_compiled = false;
    std::cout << "Fragment shader compilation error: " << infoLog << std::endl;
    return;
  }

  auto Material::compile_program() -> void
  {
    if(m_vertex_shader == 0 || m_fragment_shader == 0 || not m_v_compiled
       || not m_f_compiled) {
      m_program_compiled = false;
      return;
    }
    m_shader_program = glCreateProgram();

    glAttachShader(m_shader_program, m_vertex_shader);
    glAttachShader(m_shader_program, m_fragment_shader);
    glLinkProgram(m_shader_program);

    int success;
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);

    if(success) {
      m_program_compiled = true;
      return;
    }

    char infoLog[512];
    glGetProgramInfoLog(m_shader_program, 512, NULL, infoLog);
    m_program_compiled = false;
    m_program_error = infoLog;
    m_last_error = &m_program_error;
    std::cout << "Program linkage error: " << infoLog << std::endl;
    return;
  }
}  // namespace leng
