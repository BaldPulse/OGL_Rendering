#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec4 vertNor;

uniform mat4 lightSpaceMat;
uniform mat4 M;

void main()
{
    gl_Position = lightSpaceMat * M * vec4(vertPos.xyz, 1.0);
}