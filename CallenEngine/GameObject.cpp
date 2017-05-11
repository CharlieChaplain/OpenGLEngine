#include "GameObject.h"



GameObject::GameObject()
{
	transform = Transform();
}

GameObject::GameObject(const Model & mod, const Transform & trans)
{
	model = mod;
	transform = trans;
}

GameObject::GameObject(const Texture& tex, const Model& mod)
{
	texture = tex;
	model = mod;
	transform = Transform();
}

GameObject::GameObject(const Texture& tex, const Model& mod, const Transform& trans)
{
	texture = tex;
	model = mod;
	transform = trans;
}


GameObject::~GameObject()
{
}

int GameObject::load()
{
	return 0;
}

void GameObject::render()
{
	glUniformMatrix4fv(8, 1, GL_FALSE, &transform.transformMat[0][0]);
	texture.bind();
	model.render();
}

void GameObject::update()
{
	transform.update();
}

void GameObject::spin(float rads)
{
	transform.rotation.y += rads;
}

bool GameObject::colliding(GameObject* ob2)
{
	if (collidor.type == Sphere && ob2->collidor.type == Sphere) {
		vec3 distance = ob2->transform.position - transform.position;
		if (glm::dot(distance, distance) > pow(collidor.radius + ob2->collidor.radius, 2.f)) {
			return true;
		}
	}
	else if (collidor.type == AABB && ob2->collidor.type == AABB) {

	}
	return false;
}
