#version  330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNor;
layout(location = 2) in vec2 vertTex;
uniform mat4 P;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightPos;

//keep these and set them correctly
out vec3 fragNor;
out vec3 lightDir;
out vec3 EPos;
out vec2 vTexCoord;

void main() {

  vec4 vPosition;

  /* First model transforms */
  gl_Position = P * V *M * vec4(vertPos, 1.0);

  fragNor = (M * vec4(vertNor, 0.0)).xyz;
  lightDir = lightPos;
  // lightDir = lightPos - (M*vec4(vertPos, 1.0)).xyz;
  EPos = (V*M*vec4(vertPos, 1.0)).xyz;
  vTexCoord = vertTex;
}
