#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace ShyEngine
{
	class Collider2D;

	enum class SpriteSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct CollisionData
	{
		Collider2D* collider = nullptr;
		glm::vec2 normal = glm::vec2(0.0f, 0.0f);
		bool colliding = false;
	};

	struct PhysicsData
	{
		glm::vec2 gravity;
		float deltaTime;
		float simulationSpeed;
	};

	struct ShaderData
	{
		glm::mat4 cameraMatrix;
		glm::vec4 cameraViewport;

		float deltaTime;
	};
}