#version 420 core
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos = vec3(10, 10, 10);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform float lightIntensity = 1.0;
uniform vec4 color;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0) * lightIntensity;

  float specularStrength = 0.5;
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
  vec3 specular = specularStrength * spec * lightColor;

  FragColor = vec4((color.rgb + lightColor.rgb + specular) * diff, color.a);
}
