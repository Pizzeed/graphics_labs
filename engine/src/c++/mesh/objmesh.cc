#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include <labs_engine/glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <labs_engine/utils/types.h>
#include <labs_engine/mesh/objmesh.h>
#include <labs_engine/material/material.h>

namespace leng
{
  OBJMesh::OBJMesh(std::string const& filename, Material const& material)
    : Mesh(material)
  {
    if(not std::filesystem::exists(filename))
      std::cout << "File not found: " << filename << std::endl;

    load_file(filename);

    setup_mesh();
  }

  OBJMesh::~OBJMesh() {}

  auto OBJMesh::setup_mesh() -> void
  {
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
      GL_ARRAY_BUFFER,
      m_vertices.size() * sizeof(Vertex),
      m_vertices.data(),
      GL_STATIC_DRAW
    );
    glBufferData(
      GL_ELEMENT_ARRAY_BUFFER,
      m_indices.size() * sizeof(u32),
      m_indices.data(),
      GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void*)offsetof(Vertex, uv)
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
      2,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void*)offsetof(Vertex, normal)
    );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    m_vertex_count = m_vertices.size();
    m_index_count = m_indices.size();
    m_vertices = {};
    m_indices = {};
  }

  auto parse_vertex(std::string_view s, int& vi, int& ti, int& ni)
  {
    vi = ti = ni = 0;

    auto next = [&](std::string_view& sv) {
      size_t pos = sv.find('/');
      auto part = sv.substr(0, pos);
      sv = pos == std::string_view::npos ? "" : sv.substr(pos + 1);
      return part;
    };

    auto parse_int = [](std::string_view v) {
      int x = 0;
      std::from_chars(v.data(), v.data() + v.size(), x);
      return x;
    };

    auto p1 = next(s);
    auto p2 = next(s);
    auto p3 = s;

    if(! p1.empty())
      vi = parse_int(p1);
    if(! p2.empty())
      ti = parse_int(p2);
    if(! p3.empty())
      ni = parse_int(p3);
  }

  auto OBJMesh::load_file(std::string const& path) -> void
  {
    std::vector<glm::vec3> geometry = {};
    std::vector<glm::vec3> normal = {};
    std::vector<glm::vec2> texture = {};

    std::ifstream file(path);
    std::string line;
    std::cout << "Loading from " << path << std::endl;
    while(std::getline(file, line)) {
      std::istringstream ss(line);
      std::string prefix;
      ss >> prefix;

      if(prefix == "v") {
        glm::vec3 pos;
        ss >> pos.x >> pos.y >> pos.z;
        geometry.push_back(pos);
      }
      else if(prefix == "vt") {
        glm::vec2 uv;
        ss >> uv.x >> uv.y;
        texture.push_back(uv);
      }
      else if(prefix == "vn") {
        glm::vec3 n;
        ss >> n.x >> n.y >> n.z;
        normal.push_back(n);
      }
      else if(prefix == "f") {
        std::string vert;
        while(ss >> vert) {
          int vi = 0, ti = 0, ni = 0;
          parse_vertex(vert, vi, ti, ni);
          auto key = VertexKey {vi, ti, ni};
          if(not m_vertex_map.contains(key)) {
            auto pos = glm::vec3 {};
            auto uv = glm::vec2 {};
            auto n = glm::vec3 {};
            if(not(vi - 1 < 0 || geometry.size() <= vi - 1))
              pos = geometry[vi - 1];
            if(not(ti - 1 < 0 || texture.size() <= ti - 1))
              uv = texture[ti - 1];
            if(not(ni - 1 < 0 || normal.size() <= ni - 1))
              n = normal[ni - 1];
            m_vertices.emplace_back(pos, uv, n);
            m_vertex_map.emplace(key, static_cast<u32>(m_vertices.size() - 1));
            m_indices.push_back(m_vertices.size() - 1);
          }
          else {
            m_indices.push_back(m_vertex_map[key]);
          }
        }
      }
    }
    std::cout << "Loaded " << m_vertices.size() << " vertices" << std::endl;
  }

}  // namespace leng
