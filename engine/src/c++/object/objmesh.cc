#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <labs_engine/object/objmesh.h>

namespace leng
{
  auto OBJMesh::load_file(std::string const& path) -> std::vector<Vertex>
  {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<Vertex> outVertices;

    std::ifstream file(path);
    std::string line;
    while(std::getline(file, line)) {
      std::istringstream ss(line);
      std::string prefix;
      ss >> prefix;

      if(prefix == "v") {
        glm::vec3 pos;
        ss >> pos.x >> pos.y >> pos.z;
        positions.push_back(pos);
      }
      else if(prefix == "vt") {
        glm::vec2 uv;
        ss >> uv.x >> uv.y;
        texcoords.push_back(uv);
      }
      else if(prefix == "vn") {
        glm::vec3 n;
        ss >> n.x >> n.y >> n.z;
        normals.push_back(n);
      }
      else if(prefix == "f") {
        std::string vert;
        while(ss >> vert) {
          int vi = 0, ti = 0, ni = 0;
          sscanf(vert.c_str(), "%d/%d/%d", &vi, &ti, &ni);
          Vertex v {};
          v.position = positions[vi - 1];
          v.texcoord = texcoords[ti - 1];
          v.normal = normals[ni - 1];
          outVertices.push_back(v);
        }
      }
    }

    return outVertices;
  }

  OBJMesh::OBJMesh(std::string const& filename)
    : RenderObject()
  {
    if(not std::filesystem::exists(filename))
      std::cout << "File not found: " << filename << std::endl;
    m_vertices = load_file(filename);
    glGenBuffers(1, &m_vbo);
  }

  RenderObject::~RenderObject() {}

  auto OBJMesh::render() -> void {}
}  // namespace leng
