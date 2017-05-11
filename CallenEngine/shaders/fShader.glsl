#version 430

in vec3 fragLoc;
in vec3 fragNorm;
in vec2 fragUV;

layout (location = 12) uniform vec3 lightLoc;
layout (location = 13) uniform vec3 camLoc;

uniform sampler2D myTexture;

vec4 matComponents;  //{ ambient, diffuse, specular, brightness }

vec3 L; //unit vector of fragment to light
vec3 E; //unit vector of fragment to camera
vec3 H; //halfway vector between the two

float specAlpha = 16.f; //exponent to raise specular to


void calcVectors(){
	L = normalize(lightLoc - fragLoc);
	E = normalize(camLoc - fragLoc);
	H = normalize(L + E);
}

vec3 calcLitColor(){
	vec3 ambient = vec3(0.5f);
	vec3 diffuse = max(dot(L, fragNorm), 0) * vec3(1);
	vec3 specular = pow(max(dot(H, fragNorm), 0), specAlpha) * vec3(1);
	return ambient + diffuse + specular;
}

void main(){
	calcVectors();
	vec4 color = texture(myTexture, fragUV);
	gl_FragColor = vec4(calcLitColor() * color.xyz, color.w);
}

