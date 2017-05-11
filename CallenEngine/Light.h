#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Light
{
public:
	glm::vec3 position;
	glm::vec3 ambient;

	Light();
	Light(float x, float y, float z);
	~Light();
};

