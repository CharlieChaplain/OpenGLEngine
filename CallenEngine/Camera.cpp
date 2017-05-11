#include "Camera.h"
#include "Engine.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::start()
{
	transform = Transform(2.f);
	viewProjection = mat4();

	zoom = 1.f;
	glfwGetWindowSize(Engine::GLFWwindowPtr, &width, &height);

	fovy = glm::pi<float>() * .4f / zoom;
	aspect = (float)width / (float)height;
	zNear = .01f;
	zFar = 1000.0f;

	perspMat = glm::perspective(fovy, aspect, zNear, zFar);

	moveForce = vec3();
	transform.position = vec3(0, 0, 10); //initial location
	rotMatrix = mat3();
	maxForce = 30.0f;

	rot = vec3();
	sensitivity = .001f;
}

void Camera::update()
{

	lookMat = glm::lookAt(transform.position, transform.position + (rotMatrix * vec3(0, 0, -1)), rotMatrix * vec3(0, 1, 0));
	viewProjection = perspMat * lookMat;
}

void Camera::upload()
{
	moveAll();
	update();
	glUniformMatrix4fv(4, 1, GL_FALSE, &viewProjection[0][0]);
	glUniform3fv(13, 1, &transform.position[0]);
}

///Camera can move freely
void Camera::move()
{
	moveForce = vec3();

	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_A)) moveForce.x -= 1;
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_D)) moveForce.x += 1;
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_W)) moveForce.z -= 1;
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_S)) moveForce.z += 1;

	if (moveForce != vec3()) moveForce = normalize(moveForce) * maxForce;

	moveForce = rotMatrix * moveForce;

	transform.addForce(moveForce);
	transform.applyFriction();
	transform.update();
}

///Camera moves horizontally according to level geometry
void Camera::fpsMove()
{
	moveForce = vec3();
	vec3 planeNormal = vec3(0.f, 1.f, 0.f);

	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_A)) moveForce.x -= 1;
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_D)) moveForce.x += 1;
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_W)) moveForce.z -= 1;
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_S)) moveForce.z += 1;

	if (moveForce != vec3()) {
		vec3 projection = glm::cross(planeNormal, glm::cross(moveForce, planeNormal));
		moveForce = normalize(projection) * maxForce;
	}

	moveForce = rotMatrix * moveForce;

	transform.addForce(moveForce);
	transform.applyFriction();
	transform.position.y = 1.f;
	transform.update();
}

void Camera::turn()
{
	glfwGetWindowSize(Engine::GLFWwindowPtr, &w, &h);
	glfwGetCursorPos(Engine::GLFWwindowPtr, &mouseX, &mouseY);

	rot.y += sensitivity * (w / 2.f - mouseX);
	rot.x += sensitivity * (h / 2.f - mouseY);

	rot.x = glm::clamp(rot.x, -glm::pi<float>() /2.0f, glm::pi<float>() /2.0f);

	glfwSetCursorPos(Engine::GLFWwindowPtr, w/2, h/2);

	rotMatrix = mat3(glm::yawPitchRoll(rot.y, rot.x, 0.f));
}

void Camera::moveAll()
{
	turn();
	if (Engine::debug) move();
	else fpsMove();
}

