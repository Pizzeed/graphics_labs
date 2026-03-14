#pragma once

#include <unordered_map>

#include <glm/ext/vector_float3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

namespace leng
{
  class OBJMesh : public Mesh
  {
   public:
    OBJMesh(std::string const& filename, Material const& material);
    virtual ~OBJMesh();

   private:
    auto setup_mesh() -> void;
    auto load_file(std::string const& path) -> void;

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

    std::vector<Vertex> m_vertices = {};
    std::vector<u32> m_indices = {};
    std::unordered_map<VertexKey, u32, VertexKeyHash> m_vertex_map = {};
  };
}  // namespace leng
