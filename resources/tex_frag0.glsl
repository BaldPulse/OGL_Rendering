#version 330 core
uniform sampler2D map_ka;
uniform int use_map_ka;
uniform sampler2D map_kd;
uniform int use_map_kd;
uniform sampler2D map_color;
uniform int use_map_color;
uniform vec3 MatAmb;
uniform vec3 MatDif;
uniform vec3 MatSpec;
uniform float MatShine;
uniform vec3 MatEmit;
uniform float Alpha;
uniform int flip; 

in vec2 vTexCoord;
in vec3 fragNor;
in vec3 lightDir;
in vec3 EPos;

out vec4 Outcolor;


void main() {
	vec4 texColor0 = texture(map_color, vTexCoord);
	vec3 VecAmb = MatAmb;
	if(use_map_ka==1){
		vec3 ka = texture(map_ka, vTexCoord).xyz;
		VecAmb = ka * MatAmb;
	}
	vec3 VecDif = MatDif;
	if(use_map_kd==1){
		vec3 kd = texture(map_kd, vTexCoord).xyz;
	 	VecDif = kd * MatDif;
	}
	
	float Invert = 1.0f;
	if(flip < 1){
		 Invert = -1.0f;
	}
	vec3 normal = normalize(Invert * fragNor);
	vec3 light = normalize(lightDir);
	vec3 half_v = normalize(normalize(-EPos) + light);
	vec3 dif = VecDif*max(0.0, dot(normal, light));
	vec3 shine = MatSpec*pow(max(dot(half_v, normal), 0.0), MatShine);
	vec3 color = VecAmb +dif+shine+ MatEmit;
	
	Outcolor = vec4(color, 1.0);
}