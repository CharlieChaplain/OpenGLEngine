#include "Light.h"



Light::Light() : position(0.f, 0.f, 0.f)
{
}

Light::Light(float x, float y, float z) : position(x, y, z)
{
	ambient = glm::vec3(.2f);
}


Light::~Light()
{
}
