#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include "Timer.h"
#include "Shader.h"
#include "Camera.h"

static class Engine
{
public:
	static Timer timer;
	static GLFWwindow* GLFWwindowPtr;
	static Shader shader;
	static Shader skyboxShader;
	static bool debug;
	static bool debugBool;
	//static Camera camera;

	Engine();
	~Engine();

	static int start();
	static void stop();
	static void update();
};
