#include "Texture.h"

//ONLY SUPPORTS PNG AT THIS TIME
//TO SUPPORT OTHER TEXTURE FILE TYPES, EDIT THE LINE FIBITMAP* image = FreeImage_Load(FIF_PNG, file, PNG_DEFAULT);

Texture::Texture()
{
}

Texture::Texture(string fileName): file(fileName)
{
}


Texture::~Texture()
{
}

int Texture::load()
{
	//loads textures
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(file.c_str(), 0), file.c_str(), 0);
	if (image == nullptr) return -1;
	image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);
	
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	int width = FreeImage_GetWidth(image32Bit);
	int height = FreeImage_GetHeight(image32Bit);
	BYTE* address = FreeImage_GetBits(image32Bit);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//unbinds current texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return 0;
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::unloadAndDelete()
{
	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texID);
}
