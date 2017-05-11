#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;

layout (location = 4) uniform mat4 viewProjection;
layout (location = 8) uniform mat4 modelWorldSpace;

layout (location = 15) uniform float time;

out vec3 fragLoc;
out vec3 fragNorm;
out vec2 fragUV;
out float t;

void main(){
	fragNorm = normalize(mat3(transpose(inverse(modelWorldSpace))) * norm);
	fragLoc = vec3(modelWorldSpace * vec4(position, 1));
	fragUV = uv;
	t = time;

	gl_Position = viewProjection * vec4(fragLoc, 1);
}