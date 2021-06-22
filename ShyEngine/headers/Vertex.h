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

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
};