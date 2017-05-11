#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using glm::vec3;
using glm::vec2;

struct Vertex {
	vec3 location;
	vec2 uv;
	vec3 normal;
};

struct VertInd {
	GLuint locInd, uvInd, normInd;
};

class Model
{
private:
	GLuint vertArr;
	GLuint vertBuf;
	GLuint vertCount;
	std::string filename, file, line;

	std::vector<vec3> locations;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<VertInd> vertIndices;


public:
	Model();
	Model(std::string modelFile);
	~Model();

	bool readFile();

	bool buffer();
	bool render();
};

