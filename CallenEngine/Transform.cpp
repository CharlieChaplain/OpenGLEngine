#include "Transform.h"
#include "Engine.h"

#include <iostream>

Transform::Transform()
{
	position = vec3(0.f, 0.f, 0.f);
	rotation = vec3(0.f, 0.f, 0.f);
	scale = vec3(1.f, 1.f, 1.f);

	rigidBody.velocity = vec3();
	rigidBody.netForce = vec3();
	rigidBody.mass = 1.f;
	rigidBody.mu = 0.8f;

	transformMat = glm::translate(position) * glm::yawPitchRoll(rotation.x, rotation.y, rotation.z) * glm::scale(scale);
}

Transform::Transform(float u)
	:Transform()
{
	rigidBody.mu = u;
}

Transform::Transform(vec3 pos, vec3 rot, vec3 sc)
{
	position = pos;
	rotation = rot;
	scale = sc;

	rigidBody.velocity = vec3();
	rigidBody.netForce = vec3();
	rigidBody.mass = 1.f;
	rigidBody.mu = 0.8f;

	transformMat = glm::translate(position) * glm::yawPitchRoll(rotation.x, rotation.y, rotation.z) * glm::scale(scale);
}

Transform::Transform(vec3 pos, vec3 rot, vec3 sc, float u)
{
	position = pos;
	rotation = rot;
	scale = sc;

	rigidBody.velocity = vec3();
	rigidBody.netForce = vec3();
	rigidBody.mass = 1.f;
	rigidBody.mu = u;
	transformMat = glm::translate(position) * glm::yawPitchRoll(rotation.x, rotation.y, rotation.z) * glm::scale(scale);
}


Transform::~Transform()
{
}

void Transform::update()
{
	vec3 dv = rigidBody.netForce * Engine::timer.dt / rigidBody.mass;
	rigidBody.velocity += dv;

	vec3 dr = rigidBody.velocity * Engine::timer.dt;
	position += dr;
	transformMat = glm::translate(position) * glm::yawPitchRoll(rotation.x, rotation.y, rotation.z) * glm::scale(scale);

	rigidBody.netForce = vec3();
}

void Transform::addForce(vec3 force)
{
	rigidBody.netForce += force;
}

void Transform::applyFriction()
{
	if (rigidBody.velocity != vec3()) {
		vec3 friction = rigidBody.velocity;

		//if (friction != vec3()) friction = glm::normalize(friction);

		friction *= -rigidBody.mu;

		addForce(friction);
	}
}
