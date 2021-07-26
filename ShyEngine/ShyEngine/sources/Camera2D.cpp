#include <Camera2D.h>
#include <iostream>

namespace ShyEngine {
	Camera2D::Camera2D() : _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f), 
		_scale(1.0f), _matrixUpdated(true), _screenWidth(-1), _screenHeight(-1)
	{

	}

	void Camera2D::init(int width, int height)
	{
		this->_screenWidth = width;
		this->_screenHeight = height;

		this->_orthoMatrix = glm::ortho(0.0f, (float)this->_screenWidth, 0.0f, (float)this->_screenHeight);
		this->_matrixUpdated = true;
	}

	void Camera2D::update()
	{
		if (_matrixUpdated)
		{
			glm::vec3 translateVector(-this->_position.x, -this->_position.y, 0.0f);
			_cameraMatrix = glm::translate(this->_orthoMatrix, translateVector);

			glm::vec3 scale(this->_scale, this->_scale, 0.0f);
			_cameraMatrix = glm::scale(_cameraMatrix, scale);

			_matrixUpdated = false;
		}
	}

	void Camera2D::setPosition(glm::vec2 position)
	{
		this->_position = position;
		this->_matrixUpdated = true;
	}
	glm::vec2 Camera2D::getPosition()
	{
		return this->_position;
	}

	void Camera2D::setScale(float scale)
	{
		this->_scale = scale;
		this->_matrixUpdated = true;
	}
	float Camera2D::getScale()
	{
		return this->_scale;
	}

	glm::mat4 Camera2D::getCameraMatrix()
	{
		return this->_cameraMatrix;
	}
}