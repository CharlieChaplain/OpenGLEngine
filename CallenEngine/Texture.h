#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <string>

using std::string;

class Texture
{
private:
	GLuint texID;
	string file;
	FIBITMAP* image32Bit;

public:
	Texture();
	Texture(string fileName);
	~Texture();

	virtual int load();
	virtual void bind();
	void unloadAndDelete();
};

