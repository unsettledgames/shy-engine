#include <Camera2D.h>
#include <iostream>

namespace ShyEngine {
	Camera2D::Camera2D() {}

	void Camera2D::init(int width, int height)
	{
		this->m_screenWidth = width;
		this->m_screenHeight = height;

		this->m_orthoMatrix = glm::ortho(0.0f, (float)this->m_screenWidth, 0.0f, (float)this->m_screenHeight);
		this->m_matrixUpdated = true;
	}

	void Camera2D::update()
	{
		if (m_matrixUpdated)
		{
			// Camera scaling
			glm::vec3 scale(this->m_scale, this->m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_orthoMatrix;

			// Camera translation
			glm::vec3 translateVector(-this->m_position.x, -this->m_position.y, 0.0f);
			m_cameraMatrix = glm::translate(this->m_orthoMatrix, translateVector);

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

	bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions)
	{
		const float xRadius = dimensions.x / 2.0f;
		const float yRadius = dimensions.y / 2.0f;

		// TEST IT by multiplying scale by 2
		glm::vec2 scaledScreenDim = glm::vec2(m_screenWidth, m_screenHeight) / m_scale;

		const float minDistanceX = scaledScreenDim.x / 2 + xRadius;
		const float minDistanceY = scaledScreenDim.y / 2 + yRadius;

		glm::vec2 centerPos = position + dimensions / 2.0f;
		glm::vec2 centerCameraPos = m_position;

		glm::vec2 distance = centerPos - centerCameraPos;

		float xDepth = minDistanceX - abs(distance.x);
		float yDepth = minDistanceY - abs(distance.y);
		
		// ISSUE: use an &&
		if (xDepth > 0 || yDepth > 0)
			return true;

		return false;
	}
}