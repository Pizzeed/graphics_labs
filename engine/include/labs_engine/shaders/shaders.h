#pragma once

namespace glsl
{
  namespace color
  {
    static auto vertex =
      "#version 420 core"
      "layout(location = 0) in vec3 aPos;"
      "layout(location = 1) in vec3 aColor;"
      "out vec3 outColor;"
      "void main()"
      "{"
      "gl_Position = vec4(aPos, 1.0);"
      "outColor = aColor;"
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
      "out vec3 ourColor;"
      "out vec2 TexCoord;"
      "void main()"
      "{"
      "  gl_Position = vec4(aPos, 1.0);"
      "  ourColor = aColor;"
      "  TexCoord = aTexCoord;"
      "}";
    static auto fragment =
      "#version 420 core"
      "out vec4 FragColor;"
      "in vec3 ourColor;"
      "in vec2 TexCoord;"
      "uniform sampler2D ourTexture;"
      "void main() { FragColor = texture(ourTexture, TexCoord); }";
  }  // namespace texture
}  // namespace glsl
