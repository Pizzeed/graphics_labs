#pragma once

#include <labs_engine/utils/types.h>
#include <labs_engine/object/render_object.h>
#include <labs_engine/material/material.h>

namespace leng
{
  class Mesh : public RenderObject
  {
   public:
    Mesh(Material const& material);
    virtual ~Mesh();

   protected:
    virtual auto render(Camera const& camera) -> void override;

    Material m_material;
    bool is_material_valid = false;

    int m_vertex_count = 0;
    int m_index_count = 0;

    u32 m_model_loc = 0;
    u32 m_view_loc = 0;
    u32 m_proj_loc = 0;
  };
}  // namespace leng
