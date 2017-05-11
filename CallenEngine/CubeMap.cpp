#include "CubeMap.h"



CubeMap::CubeMap()
{
}

CubeMap::CubeMap(string fileName[])
{
	for (int i = 0; i < 6; i++) {
		file[i] = fileName[i];
	}
}

CubeMap::~CubeMap()
{
}

int CubeMap::load()
{

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++) {
		//loads textures
		FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(file[i].c_str(), 0), file[i].c_str(), 0);
		if (image == nullptr) return -1;
		if (i == 0 || i == 1 || i == 4 || i == 5) FreeImage_FlipVertical(image);
		if (i == 2) FreeImage_FlipHorizontal(image);
		image32Bit = FreeImage_ConvertTo32Bits(image);
		FreeImage_Unload(image);

		int width = FreeImage_GetWidth(image32Bit);
		int height = FreeImage_GetHeight(image32Bit);
		BYTE* address = FreeImage_GetBits(image32Bit);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
			0, 
			GL_SRGB_ALPHA, 
			width, 
			height, 
			0, 
			GL_BGRA, 
			GL_UNSIGNED_BYTE, 
			(void*)address);
		FreeImage_Unload(image32Bit);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return 0;
}

void CubeMap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
}
