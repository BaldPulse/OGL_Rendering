#version 330 core 
out vec4 color;

uniform vec3 MatAmb;
uniform vec3 MatDif;
uniform vec3 MatSpec;
uniform float MatShine;
uniform vec3 MatEmit;
uniform float Alpha;
uniform vec3 lightDir;
uniform sampler2D shadowMap;
//interpolated normal and light vector in camera space
in vec3 fragNor;
//position of the vertex in camera space
in vec3 EPos;
in vec4 FragPosLightSpace;

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

void main()
{
	//you will need to work with these for lighting
	vec3 normal = normalize(fragNor);
	vec3 light  = -normalize(lightDir);
	vec3 half_v = normalize(normalize(-EPos) + light);
	float shadow = ShadowCalculation(FragPosLightSpace);
	vec3 dif_component = MatDif*max(0.0, dot(normal, light));
	vec3 spec_component = MatSpec*pow(max(dot(half_v, normal), 0.0), MatShine);
	float trans_index = Alpha;
	if(Alpha < 0.99)
		trans_index = (trans_index + length(spec_component))/(1.0f+Alpha);
    // if(shadow==0.0)
    color = vec4(vec3((1.0-shadow), 0.0,0.0), 1.0);
    // vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
    // projCoords = projCoords * 0.5 + 0.5;
    // float closest = texture(shadowMap, projCoords.xy).r;
    // if(closest>1.0)
	//     color = vec4(vec3(1.0, 0.0,0.0), 1.0);
    // if(closest<1.0)
	//     color = vec4(vec3(0.0, 1.0,0.0), 1.0);
    // if(closest==1.0)
	//     color = vec4(vec3(0.0, 0.0,1.0), 1.0);
}
