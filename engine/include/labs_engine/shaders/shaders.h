#pragma once

namespace glsl
{
  namespace color
  {
    static auto vertex =
      "#version 420 core"
      "layout(location = 0) in vec3 aPos;"
      "layout(location = 1) in vec3 aColor;"
      "uniform mat4 model;"
      "uniform mat4 view;"
      "uniform mat4 projection;"
      "out vec3 outColor;"
      "void main()"
      "{"
      "  gl_Position = projection * view * model * vec4(aPos, 1.0);"
      "  outColor = aColor;"
      "}";
    static auto fragment =
      "#version 420 core "
      "out vec4 FragColor; "
      "in vec3 outColor; "
      "void main() { FragColor = vec4(outColor, 1.0); }";
  }  // namespace color

  namespace texture
  {
    static auto vertex =
      "#version 420 core"
      "layout(location = 0) in vec3 aPos;"
      "layout(location = 1) in vec3 aColor;"
      "layout(location = 2) in vec2 aTexCoord;"
      "out vec3 outColor;"
      "out vec2 TexCoord;"
      "uniform mat4 model;"
      "uniform mat4 view;"
      "uniform mat4 projection;"
      "void main()"
      "{"
      "  gl_Position = projection * view * model * vec4(aPos, 1.0);"
      "  outColor = aColor;"
      "  TexCoord = aTexCoord;"
      "}";
    static auto fragment =
      "#version 420 core"
      "out vec4 FragColor;"
      "in vec3 outColor;"
      "in vec2 TexCoord;"
      "uniform sampler2D outTexture;"
      "void main() { FragColor = texture(outTexture, TexCoord); }";
  }  // namespace texture
}  // namespace glsl
