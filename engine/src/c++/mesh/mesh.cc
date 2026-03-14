#include <iostream>

#include <labs_engine/glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>

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
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, m_transform.scale);

    glm::quat qx = glm::angleAxis(m_transform.rotation.x, glm::vec3(1, 0, 0));
    glm::quat qy = glm::angleAxis(m_transform.rotation.y, glm::vec3(0, 1, 0));
    glm::quat qz = glm::angleAxis(m_transform.rotation.z, glm::vec3(0, 0, 1));

    glm::quat q = qz * qy * qx;
    glm::mat4 rotation_matrix = glm::mat4(q);

    model = model * rotation_matrix;

    model = glm::translate(model, m_transform.position);

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
