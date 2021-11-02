#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace ShyEngine
{
	class Collider2D;

	/*
		This files contains the definition for data structures mainly used to pass data from the engine
		to the systems (see CollisionData, ShaderData and PhysicsData)
	*/

	/*
		\brief	Defines the possible sorting types for a batch renderer (see SpriteRenderer.h, TextRenderer.h or
			ParticleRenderer.h).
	*/
	enum class SpriteSortType
	{
		NONE,			// No sorting
		FRONT_TO_BACK,	// Sort by depth (ascending)
		BACK_TO_FRONT,	// Sort by depth (descending)
		TEXTURE_SHADER,	// Group by shader, then by texture
		TEXTURE			// Sort by texture id (ascending)
	};

	/*
		\brief Contains the data generated in a collision
	*/
	struct CollisionData
	{
		// The collider involved in the collision
		Collider2D* collider = nullptr;
		// The vector representing the normal of the collision
		glm::vec2 normal = glm::vec2(0.0f, 0.0f);
		// Has a collision happened?
		bool colliding = false;
	};

	/*
		\brief	Contains the data used by the PhysicsManager to correctly simulate physics
	*/
	struct PhysicsData
	{
		glm::vec2 gravity;
		float deltaTime;
		float simulationSpeed;
	};

	/*
		\brief	Contains the data used by renderers to draw elements on the screen
	*/
	struct ShaderData
	{
		glm::mat4 cameraMatrix;
		// Used for camera culling
		glm::vec4 cameraViewport;

		float deltaTime;
	};
}