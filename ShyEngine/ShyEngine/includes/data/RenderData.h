#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <engine/modules/collisions/Collider2D.h>

namespace ShyEngine
{
	enum class SpriteSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct ShaderData
	{
		glm::mat4 cameraMatrix;
		glm::vec4 cameraViewport;

		float deltaTime;
	};

	class RenderBatch
	{
	private:
	public:
		RenderBatch(GLuint off, GLuint numVertices, GLuint tex) : offset(off), nVertices(numVertices), texture(tex) {}

		GLuint offset;
		GLuint nVertices;
		GLuint texture;
	};
}