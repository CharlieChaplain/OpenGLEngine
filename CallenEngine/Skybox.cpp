#include "Skybox.h"


Skybox::Skybox()
{
	string fileNames[] = {"textures/skybox/skyboxR.png", "textures/skybox/skyboxL.png", "textures/skybox/skyboxT.png", "textures/skybox/skyboxB.png", "textures/skybox/skyboxBa.png", "textures/skybox/skyboxFr.png"};
	cubeMap = CubeMap(fileNames);
	model = Model("models/box.obj");
}


Skybox::~Skybox()
{
}

//for a non-static camera defined within the game (passed in with a pointer)
void Skybox::render(Camera* cam)
{
	//disables backface culling
	glDisable(GL_CULL_FACE);

	cubeMap.bind();

	vec3 initCamLoc = cam->transform.position;
	cam->transform.position = vec3();

	cam->update();
	glUniformMatrix4fv(30, 1, GL_FALSE, &cam->viewProjection[0][0]);
	

	cam->transform.position = initCamLoc;

	//disables writing to the depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	model.render();

	//reenables writing to the depth buffer
	glDepthMask(GL_TRUE);
	
}
/*
For a static camera within the engine
void Skybox::render()
{
	//disables backface culling
	glDisable(GL_CULL_FACE);

	cubeMap.bind();

	vec3 initCamLoc = Engine::camera.location;
	Engine::camera.location = vec3();

	glUniformMatrix4fv(30, 1, GL_FALSE, &Engine::camera.viewProjection[0][0]);
	Engine::camera.upload();

	Engine::camera.location = initCamLoc;
	model.render();

}
*/
