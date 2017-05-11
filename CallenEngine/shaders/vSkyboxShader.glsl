#version 430

layout (location = 0) in vec3 location;

layout (location = 30) uniform mat4 cameraWorldView;

out vec3 textureDirection;

void main(){
	textureDirection = location;
	gl_Position = cameraWorldView * vec4(location, 1);
}