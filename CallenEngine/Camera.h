#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include "Transform.h"

using glm::mat4;
using glm::mat3;
using glm::vec3;
using glm::normalize;

class Camera
{
private:

	float zoom;
	int width;
	int height;

	float fovy;
	float aspect;
	float zNear;
	float zFar;

	mat4 perspMat, lookMat;

	vec3 moveForce;
	mat3 rotMatrix;
	float maxForce;

	vec3 rot;
	float sensitivity;
	int w, h;
	double mouseX, mouseY;

public:
	mat4 viewProjection;
	Transform transform;
	vec3 location;

	Camera();
	~Camera();

	void start();
	void update();
	void upload();

	void move();
	void fpsMove();
	void turn();
	void moveAll();
};

