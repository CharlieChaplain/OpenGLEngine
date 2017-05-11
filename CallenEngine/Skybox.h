#pragma once
#include "GameObject.h"
#include "CubeMap.h"
#include "Camera.h"

#include "Engine.h"

class Skybox :
	public GameObject
{
public:
	CubeMap cubeMap;

	Skybox();
	~Skybox();

	void render(Camera* cam);
	//void render();
};

