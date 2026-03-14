#include <glm/ext/quaternion_geometric.hpp>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <labs_engine/glad/glad.h>
#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/mesh.h>
#include <labs_engine/material/material.h>

namespace leng
{
  Mesh::Mesh(Material const& material)
    : m_material(material)
    , RenderObject()
  {
    if(not m_material.is_valid()) {
      std::cout << "Material not valid" << std::endl;
      return;
    }
    m_model_loc = glGetUniformLocation(m_material.program(), "model");
    m_view_loc = glGetUniformLocation(m_material.program(), "view");
    m_proj_loc = glGetUniformLocation(m_material.program(), "projection");
  }

  Mesh::~Mesh() {}

  auto Mesh::render(Camera const& camera) -> void
  {
    if(not m_material.is_valid()) {
      return;
    }
    glm::mat4 id = glm::mat4(1.0f);

    glm::mat4 S = glm::scale(id, m_transform.scale);
    glm::mat4 T = glm::translate(id, m_transform.position);

    auto const& rot = m_transform.rotation;
    auto rx = glm::radians(rot.x) * .5;
    auto ry = glm::radians(rot.y) * .5;
    auto rz = glm::radians(rot.z) * .5;

    glm::quat q = glm::normalize(glm::quat {1, {rx, ry, rz}});
    glm::mat4 R = glm::toMat4(q);
    glm::mat4 model = T * R * S;

    auto view = camera.view_matrix();
    auto proj = camera.projection_matrix();

    glBindVertexArray(m_vao);
    glUseProgram(m_material.program());
    glUniformMatrix4fv(m_model_loc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(m_view_loc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(m_proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}  // namespace leng
