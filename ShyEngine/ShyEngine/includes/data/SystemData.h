#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace ShyEngine
{
	enum class SpriteSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct PhysicsData
	{
		glm::vec2 gravity;
		float deltaTime;
	};

	struct ShaderData
	{
		glm::mat4 cameraMatrix;
		glm::vec4 cameraViewport;

		float deltaTime;
	};
}