#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <string>
#include <fstream>

using std::string;

class Shader
{
private:
	GLuint program, vprogram, fprogram;
	string filenamev;
	string filenamef;

	char* readBinaryFile(std::string filename);

public:
	Shader();
	~Shader();

	bool load(string v, string f);
	bool compile(GLenum shaderType);
	void use();
	void unload();
};

