#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 lightSpaceMat;

//keep these and set them correctly
out vec3 fragNor;
out vec3 EPos;
out vec4 FragPosLightSpace;

void main()
{
	gl_Position = P * V * M * vertPos;
	//update these as needed
	fragNor = (M * vec4(vertNor, 0.0)).xyz; 
	EPos = (V*M*vertPos).xyz;
	FragPosLightSpace = lightSpaceMat* vec4(EPos, 1.0);
}
