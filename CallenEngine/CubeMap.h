#pragma once
#include "Texture.h"

class CubeMap :
	public Texture
{
private:
	GLuint texID;
	string file[6];
	FIBITMAP* image32Bit;

public:
	CubeMap();
	CubeMap(string fileName[]);
	~CubeMap();

	int load() override;
	void bind() override;
};

