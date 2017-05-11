#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <iostream>
#include <vector>
#include <ctime>

#include "Engine.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "Texture.h"
#include "GameObject.h"
#include "Skybox.h"

Camera camera = Camera();
Model model = Model("models/keg.obj");
Model model2 = Model("models/crate.obj");
Model box = Model("models/box.obj");
Model sphere = Model("models/sphere.obj");
Texture tex = Texture("textures/keg_texture.png");
Texture crateTex = Texture("textures/crate_texture.png");
Texture groundTex = Texture("textures/test_texture.png");
Skybox skybox = Skybox();

Light light = Light(10.f, 10.f, 10.f);

int main() {

	if(Engine::start() == -1) return -1;

	//buffers all models
	model.buffer();
	box.buffer();
	sphere.buffer();
	model2.buffer();
	skybox.model.buffer();
	
	//loads all textures
	if (groundTex.load() == -1)	return -1;
	if (tex.load() == -1)	return -1;
	if (crateTex.load() == -1)	return -1;
	if (skybox.cubeMap.load() == -1) return -1;

	//inits camera
	camera.start();

	//hides cursor
	glfwSetInputMode(Engine::GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//enables wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
	

	//creates game objects
	Transform groundTr = Transform(vec3(0.f, -5.f, 0.f), vec3(), vec3(20.f, 0.5f, 20.f));
	GameObject ground = GameObject(box, groundTr);

	Transform kegTr = Transform(vec3(10.f, 0.f, 0.f), vec3(), vec3(1.f));
	GameObject keg = GameObject(tex, model, kegTr);

	Transform tr = Transform(vec3(-10.f, 0.f, 0.f), vec3(), vec3(1.f));
	GameObject crate = GameObject(crateTex, model2, tr);
	crate.transform.rigidBody.mu = 0.8f;

	keg.collidor.type = Sphere;
	keg.collidor.radius = 1.f;

	crate.collidor.type = Sphere;
	crate.collidor.radius = 1.f;

	GameObject collidor1 = GameObject(groundTex, sphere, tr);
	GameObject collidor2 = GameObject(groundTex, sphere, kegTr);

	//game loop
	while (!glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_ESCAPE)) {

		//updates engine and all gameobjects
		Engine::update();
		camera.upload();

		crate.transform.addForce(vec3(1.f, 0.f, 0.f));
		crate.transform.applyFriction();
		
		if (keg.colliding(&crate)) {
			keg.transform.rotation += vec3(0.f, 1.f, 0.f);
			std::cout << "colliding\n";
		}

		crate.update();
		keg.update();

		collidor1.transform.position = crate.transform.position;
		collidor2.transform.position = keg.transform.position;

		collidor1.update();
		collidor2.update();

		//Draw buffered models
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//renders skybox

		Engine::skyboxShader.use();
		skybox.render(&camera);
		//skybox.render();


		//passes in values to the shaders
		Engine::shader.use();

		//uniform at location 4 is worldView, uploaded in camera.upload()
		//uniform at location 8 is transform matrix, uploaded in model.render()
		glUniform3fv(12, 1, &(light.position[0]));
		//uniform at location 13 is camera location, uploaded in camera.upload()
		glUniform1f(15, Engine::timer.t);
		

		//render game objects

		//enables backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		//ground
		ground.render();
		//keg
		keg.render();
		//crate
		crate.render();

		collidor1.render();
		collidor2.render();

		//unbind an object after drawing it

		//swap the front (what the screen displays) and back (what opengl draws to) buffers.
		glfwSwapBuffers(Engine::GLFWwindowPtr);

		//Process queued window, mouse & keyboard callback events
		glfwPollEvents();

	}

	tex.unloadAndDelete();
	crateTex.unloadAndDelete();
	Engine::shader.unload();
	Engine::skyboxShader.unload();
	Engine::stop();
	return 0;
}