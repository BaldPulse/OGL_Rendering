#version 330 core 
out vec4 color;

uniform vec3 MatAmb;
uniform vec3 MatDif;
uniform vec3 MatSpec;
uniform float MatShine;
uniform vec3 MatEmit;
uniform float Alpha;
uniform vec3 lightDir;
//interpolated normal and light vector in camera space
in vec3 fragNor;
//position of the vertex in camera space
in vec3 EPos;

void main()
{
	//you will need to work with these for lighting
	vec3 normal = normalize(fragNor);
	vec3 light  = normalize(lightDir);
	vec3 half_v = normalize(normalize(-EPos) + light);
	vec3 spec_component = MatSpec*pow(max(dot(half_v, normal), 0.0), MatShine);
	float trans_index = Alpha;
	if(Alpha < 0.99)
		trans_index = (trans_index + length(spec_component))/(1.0f+Alpha);
	color = vec4((MatAmb + MatDif*max(0.0, dot(normal, light)) + spec_component + MatEmit), trans_index);
}
