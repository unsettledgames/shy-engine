#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <data/ColorRGBA8.h>

namespace ShyEngine
{
	/*
		\brief	Represents a bidimensional position in the space

		No, we can't use a glm::vec2 because the Vertex struct is passed to OpenGL and it needs to be as small
		as possible in order for it to be efficient.
	*/
	typedef struct _position
	{
		float x;
		float y;
	} Position;

	/*
		\brief	Represents the UVs of a texture. See the struct Position on why this isn't a glm::vec2.
	*/
	typedef struct _uv
	{
		float u;
		float v;
	} UV;

	/*
		\brief	Represents a Vertex
	*/
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

		void setPosition(glm::vec2 pos)
		{
			position.x = pos.x;
			position.y = pos.y;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}
