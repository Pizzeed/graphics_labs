#version 420 core
out vec4 FragColor;

void main()
{
  vec3 objectColor = vec3(1, 1, 1);

  FragColor = vec4(objectColor, 1.0);
}
