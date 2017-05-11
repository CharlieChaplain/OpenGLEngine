#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>


#include "Transform.h"
#include "Texture.h"
#include "Model.h"

struct Collidor {
	CollidorType type = none;
	float radius;
	vec3 corner;
};



class GameObject
{
public:
	Transform transform;
	Texture texture;
	Model model;

	Collidor collidor;

	GameObject();
	GameObject(const Model& mod, const Transform& trans);
	GameObject(const Texture& tex, const Model& mod);
	GameObject(const Texture& tex, const Model& mod, const Transform& trans);
	~GameObject();

	virtual int load();
	virtual void render();
	virtual void update();
	void spin(float rads);

	bool colliding(GameObject* ob2);
};

