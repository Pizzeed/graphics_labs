#pragma once

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

    friend void Application::run_graphics_loop();

   private:
    struct Vertex
    {
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 texcoord;
    };

    auto load_file(std::string const& path) -> std::vector<Vertex>;

    std::vector<Vertex> m_vertices = {}
  };
}  // namespace leng
