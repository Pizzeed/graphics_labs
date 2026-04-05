#version 420 core
in vec3 FragPos;
in vec3 Normal;
in vec2 Uv;

out vec4 FragColor;

uniform vec3 lightPos = vec3(10, 10, 10);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform float lightIntensity = 1.0;
uniform sampler2D inTexture;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 objectColor = vec3(1, 1, 1);

  float diff = max(dot(norm, lightDir), 0.0) * lightIntensity;

  vec3 color = (objectColor.rgb + lightColor.rgb) * diff;

  FragColor = texture(inTexture, Uv) * vec4(color, 1.0);
}
