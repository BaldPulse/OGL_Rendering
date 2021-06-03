#version 330 core
uniform sampler2D map_ka;
uniform int use_map_ka;
uniform sampler2D map_kd;
uniform int use_map_kd;
uniform sampler2D map_ks;
uniform int use_map_ks;
uniform vec3 MatAmb;
uniform vec3 MatDif;
uniform vec3 MatSpec;
uniform float MatShine;
uniform vec3 MatEmit;
uniform float Alpha;
uniform int flip; 
uniform vec3 lightDir;
uniform sampler2D shadowMap;


in vec2 vTexCoord;
in vec3 fragNor;
in vec3 EPos;
in vec4 FragPosLightSpace;

out vec4 Outcolor;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    float shadow;
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    if(projCoords.z > 1.0){
        shadow = 0.0;
    }
    else{
        // transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        
        // get depth of current fragment from light's perspective
        float currentDepth = projCoords.z;
        float bias = max(0.05 * (1.0 - dot(fragNor, normalize(lightDir))), 0.005);  
         
        //PCF version
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
                shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            }    
        }
        shadow /= 9.0;
    }
	return shadow;       
}  

void main() {
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
	vec3 VecSpec = MatSpec;
	vec3 ks;
	if(use_map_ks==1){
		ks = texture(map_ks, vTexCoord).xyz;
	 	VecSpec = ks * MatSpec;
	}
	
	float Invert = 1.0f;
	if(flip < 1){
		 Invert = -1.0f;
	}
	vec3 normal = normalize(Invert * fragNor);
	vec3 light  = -normalize(lightDir);
	vec3 half_v = normalize(normalize(-EPos) + light);
	float shadow = ShadowCalculation(FragPosLightSpace);
	vec3 dif = VecDif*max(0.0, dot(normal, light));
	vec3 shine = VecSpec*pow(max(dot(half_v, normal), 0.0), MatShine);
	vec3 color = VecAmb +(1.0-shadow)*(dif+shine)+ MatEmit;
	
	Outcolor = vec4(color, 1.0);
}