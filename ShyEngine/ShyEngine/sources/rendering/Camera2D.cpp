#include <rendering/Camera2D.h>
#include <iostream>

namespace ShyEngine {
	Camera2D::Camera2D() {}

	void Camera2D::init(int width, int height)
	{
		this->m_screenWidth = width;
		this->m_screenHeight = height;

		this->m_orthoMatrix = glm::ortho(0.0f, (float)this->m_screenWidth / m_scale, 0.0f, (float)this->m_screenHeight / m_scale);
		this->m_matrixUpdated = true;
	}

	void Camera2D::update()
	{
		if (m_matrixUpdated)
		{
			// Camera translation
			glm::vec3 translateVector(-this->m_position.x + m_screenWidth / 2, -this->m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(this->m_orthoMatrix, translateVector);

			// Camera scaling
			glm::vec3 scale(this->m_scale, this->m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

			m_matrixUpdated = false;
		}
	}

	void Camera2D::setPosition(glm::vec2 position)
	{
		this->m_position = position;
		this->m_matrixUpdated = true;
	}
	glm::vec2 Camera2D::getPosition()
	{
		return this->m_position;
	}

	void Camera2D::setScale(float scale)
	{
		this->m_scale = scale;
		this->m_matrixUpdated = true;
	}
	float Camera2D::getScale()
	{
		return this->m_scale;
	}

	glm::mat4 Camera2D::getCameraMatrix()
	{
		return this->m_cameraMatrix;
	}

	glm::vec2 Camera2D::screenToWorld(glm::vec2 screenCoords)
	{
		// Convert to a system where (0,0) is the center of the screen
		screenCoords.y = m_screenHeight - screenCoords.y;
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		// Take scaling in account
		screenCoords /= m_scale;
		// Convert to world position
		screenCoords += m_position;

		return screenCoords;
	}

	glm::vec4 Camera2D::getViewportRect()
	{
		return glm::vec4(m_position, glm::vec2(m_screenWidth, m_screenHeight) / m_scale);
	}
}