#include <iostream>
#include <array>
#include <random>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>
#include <labs_engine/glad/glad.h>

#include <particles/particle_attractor.h>
#include <shapes/tetrahedron_emitter.h>

TetrahedronEmitter::TetrahedronEmitter(
  leng::Material* material,
  std::shared_ptr<RenderObject> const& particle_template,
  f32 size
)
  : leng::Mesh(material)
  , IParticleEmitter(particle_template)
  , m_size(size)
{
  m_rng = std::mt19937(std::random_device {}());

  float const s = m_size / 2.0f;

  struct Vertex
  {
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec3 normal;
  };

  std::array<Vertex, 12> out;
  int idx = 0;

  auto h = m_size * std::sqrt(2.f / 3.f);
  auto m_1 = ((m_size * (std::sqrt(3.f) / 2.f)) / 3.f);
  auto m_2 = m_1 * 2.f;
  auto half_s = m_size * .5f;
  // clang-format off
  m_vertices = {
    {0, h, 0},  
    {0, 0, -m_2},
    {-half_s, 0, m_1},
    {half_s, 0, m_1}};
  int faces[4][3] = {
    {0, 1, 2}, 
    {0, 3, 1}, 
    {0, 2, 3}, 
    {1, 3, 2}
  };
  // clang-format on

  glm::vec2 uv[3] = {{0, 0}, {1, 0}, {0.5f, 1}};

  for(int f = 0; f < 4; ++f) {
    glm::vec3 a0 = m_vertices[faces[f][0]];
    glm::vec3 a1 = m_vertices[faces[f][1]];
    glm::vec3 a2 = m_vertices[faces[f][2]];

    glm::vec3 normal = glm::normalize(glm::cross(a1 - a0, a2 - a0));

    for(int i = 0; i < 3; ++i) {
      out[idx++] = {m_vertices[faces[f][i]], uv[i], normal};
    }
  }
  glBindVertexArray(m_buffer->vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffer->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer->ebo);
  glBufferData(
    GL_ARRAY_BUFFER,
    out.size() * sizeof(Vertex),
    out.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, pos)
  );

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, uv)
  );

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, normal)
  );
  glBindVertexArray(0);
}

auto TetrahedronEmitter::render(leng::Camera const& camera) -> void
{
  if(not m_material->is_valid()) {
    return;
  }
  glm::mat4 id = glm::mat4(1.0f);

  glm::mat4 S = glm::scale(id, m_transform.scale);
  glm::mat4 T = glm::translate(id, m_transform.position);

  auto const& rot = m_transform.rotation;
  auto rx = glm::
    rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1.f, 0.f, 0.f));
  auto ry = glm::
    rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0.f, 1.f, 0.f));
  auto rz = glm::
    rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0.f, 0.f, 1.f));

  glm::mat4 R = rz * ry * rx;
  glm::mat4 model = T * R * S;

  auto view = camera.view_matrix();
  auto proj = camera.projection_matrix();

  glBindVertexArray(m_buffer->vao);
  m_material->use();

  glUniformMatrix4fv(m_model_loc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(m_view_loc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(m_proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

  glDrawArrays(GL_TRIANGLES, 0, 12);
  glBindVertexArray(0);
}

auto TetrahedronEmitter::tick(f32 const delta) -> void
{
  for(auto& p : m_particles) {
    auto scale = std::
      max(1.f, glm::distance(p.spawn_pos, p.body->transform().position));
    p.body->transform().scale = glm::vec3(scale, scale, scale);
  }

  for(auto const& attractor : m_attractors) {
    glm::vec3 plane_pos = dynamic_pointer_cast<RenderObject>(attractor)
                            ->transform()
                            .position;
    glm::vec3 plane_normal = glm::vec3 {0.f, 1.f, 0.f};

    for(auto& p : m_particles) {
      glm::vec3 closest = attractor->closest_point(
        p.body->transform().position
      );
      glm::vec3 to_plane = p.body->transform().position - plane_pos;
      glm::vec3 dir = closest - p.body->transform().position;
      f32 dist = glm::length(dir);

      float pull_strength = attractor->force() * delta;
      if(dist > 0.f) {
        p.velocity += glm::normalize(-to_plane) * pull_strength;
      }
      else {
        float vn = glm::dot(p.velocity, plane_normal);
        p.velocity -= plane_normal * vn;
      }
    }
  }

  for(auto& p : m_particles) {
    p.velocity.x *= 1.0f - 0.75f * delta;
    p.velocity.y += (m_start_speed - p.velocity.y) * 0.5f * delta;
    p.velocity.z *= 1.0f - 0.75f * delta;
  }

  tick_particles(delta);
}

auto sample_triangle(
  glm::vec3 const& a,
  glm::vec3 const& b,
  glm::vec3 const& c,
  std::mt19937& rng
) -> glm::vec3
{
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  float r1 = dist(rng);
  float r2 = dist(rng);

  if(r1 + r2 > 1.0f) {
    r1 = 1.0f - r1;
    r2 = 1.0f - r2;
  }

  return a + r1 * (b - a) + r2 * (c - a);
}

auto TetrahedronEmitter::get_random_point() -> std::pair<glm::vec3, glm::vec3>
{
  // need to optimize this same shit in the engine and make setters virtual
  m_real_vertices = m_vertices;
  glm::mat4 id = glm::mat4(1.0f);

  glm::mat4 S = glm::scale(id, m_transform.scale);
  glm::mat4 T = glm::translate(id, m_transform.position);

  auto const& rot = m_transform.rotation;
  auto rx = glm::
    rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1.f, 0.f, 0.f));
  auto ry = glm::
    rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0.f, 1.f, 0.f));
  auto rz = glm::
    rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0.f, 0.f, 1.f));

  glm::mat4 R = rz * ry * rx;
  glm::mat4 model = T * R * S;
  for(auto& v : m_real_vertices)
    v = glm::vec3(model * glm::vec4(v, 1.0f));

  constexpr std::array<std::array<int, 4>, 4> faces = {
    {{{0, 1, 2, 3}}, {{0, 1, 3, 2}}, {{0, 2, 3, 1}}, {{1, 2, 3, 0}}}
  };

  std::uniform_int_distribution<int> face_dist(0, 3);
  int f = face_dist(m_rng);

  auto const& tri = faces[f];
  auto a = m_real_vertices[tri[0]];
  auto b = m_real_vertices[tri[1]];
  auto c = m_real_vertices[tri[2]];
  auto d = m_real_vertices[tri[3]];

  auto pt = sample_triangle(a, b, c, m_rng);
  auto n = glm::cross((b - a), (c - a));
  if(glm::dot(n, (d - a)) > 0.0f)
    n = -n;
  n = glm::normalize(n);
  return {pt, n};
}

auto TetrahedronEmitter::emit_particle() -> void
{
  auto [pos, vel] = get_random_point();

  auto body = static_pointer_cast<RenderObject>(
    m_particle_template->clone(false)
  );
  auto particle = IParticleEmitter::
    Particle {body, vel * m_start_speed, pos, m_particle_lifetime, {}};
  body->set_position(pos);
  this->scene()->add_object(body);
  m_particles.push_back(particle);
}

auto TetrahedronEmitter::clone(bool on_scene) -> std::shared_ptr<leng::Object>
{
  auto obj = std::make_shared<TetrahedronEmitter>(*this);
  if(on_scene and this->scene())
    this->scene()->add_object(obj);

  obj->m_model_loc = this->m_model_loc;
  obj->m_view_loc = this->m_view_loc;
  obj->m_proj_loc = this->m_proj_loc;

  return obj;
}

auto TetrahedronEmitter::add_attractor(
  std::shared_ptr<IParticleAttractor> const& attractor
) -> void
{
  m_attractors.push_back(attractor);
}
