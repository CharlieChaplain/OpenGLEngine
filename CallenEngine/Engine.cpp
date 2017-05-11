#include "Engine.h"
#include <iostream>

Timer Engine::timer;
GLFWwindow* Engine::GLFWwindowPtr;
Shader Engine::shader;
Shader Engine::skyboxShader;
bool Engine::debug;
bool Engine::debugBool;
//Camera Engine::camera;

Engine::Engine()
{
}


Engine::~Engine()
{
}

int Engine::start()
{
	debug = false;
	debugBool = 0.2f;

	//trys to init GLFW
	if (glfwInit() != GL_TRUE) {
		printf("Failed to init GLFW\n");
		return -1;
	}

	//implements multisample anti-aliasing (4 samples)
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	//Creates window
	GLFWwindowPtr = glfwCreateWindow(800, 600, "Callen DSA1 Engine", NULL, NULL);
	
	//Makes it the currently active window, or quits
	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return -1;
	}

	//initializes GLEW or quits
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	//loads engine shader
	if (!Engine::shader.load("shaders/vShader.glsl", "shaders/fShader.glsl")) {
		glfwTerminate();
		std::cin.get();
		return -1;
	}

	//loads skybox shader
	if (!Engine::skyboxShader.load("shaders/vSkyboxShader.glsl", "shaders/fSkyboxShader.glsl")) {
		glfwTerminate();
		std::cin.get();
		return 1;
	}

	//loads camera
	//Engine::camera.start();

	return 0;
}

void Engine::stop()
{
	glfwTerminate();
}

void Engine::update()
{
	timer.update();

	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_F1) && !debugBool) {
		Engine::debug = !Engine::debug;
		debugBool = true;
	}
	if (!glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_F1)) debugBool = false;
	std::cout << debug << "\n";
	
	system("cls");
}