#pragma once

#include <unordered_map>

#include <glm/ext/vector_float3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/object/render_object.h>
#include <labs_engine/material/material.h>
#include <labs_engine/application/application.h>

namespace leng
{
  class OBJMesh : public RenderObject
  {
   public:
    OBJMesh(std::string const& filename, Material const& material);
    virtual ~OBJMesh();

    virtual auto tick(int const delta) -> void override;

   protected:
    virtual auto render() -> void override;

    virtual auto setup_mesh() -> void;

    friend void Application::run_graphics_loop();

   private:
    auto load_file(std::string const& path) -> void;

    Material m_material;
    bool is_material_valid = false;

    struct Vertex
    {
      glm::vec3 pos = {};
      glm::vec2 uv = {};
      glm::vec3 normal = {};
    };

    struct VertexKey
    {
      int pos_idx = -1;
      int uv_idx = -1;
      int normal_idx = -1;

      bool operator==(VertexKey const&) const = default;
    };

    struct VertexKeyHash
    {
      inline auto operator()(VertexKey const& k) const -> size_t
      {
        return (k.pos_idx * 73'856'093) ^ (k.uv_idx * 19'349'663)
             ^ (k.normal_idx * 83'492'791);
      }
    };

    int m_vertex_count = 0;
    int m_index_count = 0;
    std::vector<Vertex> m_vertices = {};
    std::vector<u32> m_indices = {};
    std::unordered_map<VertexKey, u32, VertexKeyHash> m_vertex_map = {};

    u32 m_model_loc = 0;
    u32 m_view_loc = 0;
    u32 m_proj_loc = 0;
  };
}  // namespace leng
