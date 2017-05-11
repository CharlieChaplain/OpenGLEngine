#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using glm::vec3;
using glm::mat4;

struct RigidBody {
	vec3 velocity;
	vec3 netForce;
	float mass;
	float mu;
};

enum CollidorType {
	Sphere,
	AABB,
	none
};

class Transform
{
public:
	vec3 position, rotation, scale;

	mat4 transformMat;

	RigidBody rigidBody;
	
	Transform();
	Transform(float u);
	Transform(vec3 pos, vec3 rot, vec3 sc);
	Transform(vec3 pos, vec3 rot, vec3 sc, float u);
	~Transform();

	void update();
	void addForce(vec3 force);
	void applyFriction();
};

