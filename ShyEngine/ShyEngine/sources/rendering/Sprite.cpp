#include <rendering/Sprite.h>

namespace ShyEngine {
	Sprite::Sprite(float x, float y, float width, float height, std::string texturePath)
	{
		this->m_xPos = x;
		this->m_yPos = y;
		this->m_width = width;
		this->m_height = height;

		this->m_buffer = 0;
		this->m_texture = ResourcesManager::getTexture(texturePath);

		// Initializing the sprite
		// Creating the buffer if I haven't yet
		if (m_buffer == 0)
			glGenBuffers(1, &m_buffer);

		//First Triangle
		// Top right
		m_vertexData[0].setPosition(m_xPos + m_width, m_yPos + m_height);
		m_vertexData[0].setUV(1.0f, -1.0f);

		// Top left
		m_vertexData[1].setPosition(m_xPos, m_yPos + m_height);
		m_vertexData[1].setUV(0.0f, -1.0f);

		// Bottom left
		m_vertexData[2].setPosition(m_xPos, m_yPos);
		m_vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		// Bottom left
		m_vertexData[3].setPosition(m_xPos, m_yPos);
		m_vertexData[3].setUV(0.0f, 0.0f);

		// Bottom right
		m_vertexData[4].setPosition(m_xPos + m_width, m_yPos);
		m_vertexData[4].setUV(1.0f, 0.0f);

		// Top right
		m_vertexData[5].setPosition(m_xPos + m_width, m_yPos + m_height);
		m_vertexData[5].setUV(1.0f, -1.0f);

		for (int i = 0; i < 6; i++)
			m_vertexData[i].setColor(255, 0, 255, 255);

		m_vertexData[2].setColor(0, 0, 255, 255);
		m_vertexData[5].setColor(0, 255, 0, 255);

		// Putting the vertex data into the buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Sprite::~Sprite()
	{
		// Cleaning the buffer if I was using it
		if (this->m_buffer != 0)
			glDeleteBuffers(1, &m_buffer);
	}

	void Sprite::render()
	{
		// OPTIMIZABLE: check if it's already binded
		glBindTexture(GL_TEXTURE_2D, m_texture.id);
		// Binding the buffer and sending the vertex data
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

		// Enabling arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Bind position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// Bind color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// Bind UVs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Disabling arrays
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		// Unbinding buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}