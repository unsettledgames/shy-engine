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

		void setPosition(glm::vec2 position);
		glm::vec2 getPosition();

		void setScale(float scale);
		float getScale();

		glm::mat4 getCameraMatrix();

		void update();

		void init(int width, int height);
	};
}