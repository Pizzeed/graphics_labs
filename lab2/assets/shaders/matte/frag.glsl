#version 420 core
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 lightPos = vec3(10, 10, 10);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec4 color;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);

  float diff = max(dot(norm, lightDir), 0.0);

  FragColor = vec4(color.rgb * diff + lightColor.rgb * diff * .3, color.a);
}
