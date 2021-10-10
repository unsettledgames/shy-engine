#pragma once

#include <GL/glew.h>

/*
	\brief	Represents a Texture
*/
typedef struct texture
{
	GLuint id;
	int width;
	int height;
} Texture;