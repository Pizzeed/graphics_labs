#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include <labs_engine/glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <labs_engine/glad/glad.h>
#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/objmesh.h>

namespace leng
{
  OBJMesh::OBJMesh(std::string const& filename)
    : RenderObject()
  {
    if(not std::filesystem::exists(filename))
      std::cout << "File not found: " << filename << std::endl;
    load_file(filename);

    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      6 * sizeof(f32),
      (void*)(3 * sizeof(f32))
    );
    glEnableVertexAttribArray(1);

    glBufferData(
      GL_ARRAY_BUFFER,
      m_geometry.size() * sizeof(f32),
      m_geometry.data(),
      GL_STATIC_DRAW
    );

    glBindVertexArray(0);
  }

  OBJMesh::~OBJMesh()
  {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_vao);
  }

  auto OBJMesh::render() -> void {}

  auto OBJMesh::load_file(std::string const& path) -> void
  {
    m_geometry = {};
    m_normal = {};
    m_texture = {};

    std::ifstream file(path);
    std::string line;
    while(std::getline(file, line)) {
      std::istringstream ss(line);
      std::string prefix;
      ss >> prefix;

      if(prefix == "v") {
        glm::vec3 pos;
        ss >> pos.x >> pos.y >> pos.z;
        m_geometry.push_back(pos);
      }
      else if(prefix == "vt") {
        glm::vec2 uv;
        ss >> uv.x >> uv.y;
        m_texture.push_back(uv);
      }
      else if(prefix == "vn") {
        glm::vec3 n;
        ss >> n.x >> n.y >> n.z;
        m_normal.push_back(n);
      }
      else if(prefix == "f") {
        std::string vert;
        while(ss >> vert) {
          int vi = 0, ti = 0, ni = 0;
          sscanf(vert.c_str(), "%d/%d/%d", &vi, &ti, &ni);
        }
      }
    }
  }

}  // namespace leng
