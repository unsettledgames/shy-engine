#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <data/ColorRGBA8.h>

namespace ShyEngine
{
	typedef struct _position
	{
		float x;
		float y;
	} Position;

	typedef struct _uv
	{
		float u;
		float v;
	} UV;

	struct Vertex
	{
		Position position;
		ColorRGBA8 color;
		UV uv;

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color = ColorRGBA8(r, g, b, a);
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
}
