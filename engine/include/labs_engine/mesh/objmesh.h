#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/application/application.h>
#include <labs_engine/object/render_object.h>

namespace leng
{
  class OBJMesh : public RenderObject
  {
   public:
    OBJMesh(std::string const& filename);
    virtual ~OBJMesh();

   protected:
    virtual auto render() -> void override;

    virtual auto setup_mesh() -> void override;

    friend void Application::run_graphics_loop();

   private:
    auto load_file(std::string const& path) -> void;

    std::vector<glm::vec3> m_geometry = {};
    std::vector<glm::vec3> m_normal = {};
    std::vector<glm::vec2> m_texture = {};
  };
}  // namespace leng
