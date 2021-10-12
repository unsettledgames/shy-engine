#pragma once

#include <GL/glew.h>

/*
	\brief	Represents a Texture
*/
typedef struct texture
{
	GLuint id;
	GLint textureFiltering = GL_NEAREST;
	GLint mipmapFiltering = GL_NEAREST_MIPMAP_NEAREST;

	int width;
	int height;
} Texture;