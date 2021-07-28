#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ShyEngine {

	class Camera2D
	{
	private:
		// OPTIMIZABLE: position should be part of some kind of transform component
		glm::vec2 _position;

		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;

		float _scale;
		bool _matrixUpdated;

		int _screenWidth;
		int _screenHeight;

	public:

		Camera2D();

		/*
			Gets / sets the position
		*/
		void setPosition(glm::vec2 position);
		glm::vec2 getPosition();

		/*
			Gets / sets the scake
		*/
		void setScale(float scale);
		float getScale();

		/*
			Returns the camera matrix
		*/
		glm::mat4 getCameraMatrix();

		/*
			Updates the camera
		*/
		void update();

		/*
			Initializes the camera
		*/
		void init(int width, int height);

		/*
			Converts screenCoords (in screen position) to world position
		*/
		glm::vec2 screenToWorld(glm::vec2 screenCoords);

		/*
			Checks whether or not the box passed as a parameter is in the camera view
		*/
		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);
	};
}