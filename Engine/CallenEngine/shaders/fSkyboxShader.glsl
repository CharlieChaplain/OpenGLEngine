#version 430

in vec3 textureDirection;

uniform samplerCube cubemap;

void main(){
	gl_FragColor = texture(cubemap, textureDirection);
}