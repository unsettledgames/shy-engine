#pragma once

#include <GL/glew.h>

typedef struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Color;

typedef struct position
{
	float x;
	float y;
} Position;

typedef struct uv
{
	float u;
	float v;
} UV;

struct Vertex
{
	Color color;
	Position position;
	UV uv;

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
};