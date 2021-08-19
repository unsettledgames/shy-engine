#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <data/ColorRGBA8.h>

namespace ShyEngine
{
	struct Vertex
	{
		ColorRGBA8 color;
		glm::vec2 position;
		glm::vec2 uv;

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
			uv.x = u;
			uv.y = v;
		}
	};
}
