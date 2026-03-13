#pragma once
#include <string>

#include <labs_engine/utils/types.h>

namespace leng
{
  class Material
  {
   public:
    Material(
      std::string const& vertex_shader,
      std::string const& fragment_shader
    );
    ~Material();

    static auto from_files(
      std::string const& vertex_shader_filename,
      std::string const& fragment_shader_filename
    ) -> Material;

    auto is_valid() const -> bool;

    auto program() const -> u32;

    auto last_error() const -> std::string;
    auto vertex_error() const -> std::string;
    auto fragment_error() const -> std::string;
    auto program_error() const -> std::string;

   protected:
    auto compile_vertex() -> void;
    auto compile_fragment() -> void;
    auto compile_program() -> void;

    bool m_v_compiled = false;
    bool m_f_compiled = false;
    bool m_program_compiled = false;

    u32 m_vertex_shader = 0;
    u32 m_fragment_shader = 0;
    u32 m_shader_program = 0;

    std::string m_v_src = "";
    std::string m_f_src = "";

    std::string* m_last_error = nullptr;
    std::string m_vertex_error = "";
    std::string m_fragment_error = "";
    std::string m_program_error = "";
  };
}  // namespace leng
