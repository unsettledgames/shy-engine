#include <Sprite.h>

namespace ShyEngine {
	Sprite::Sprite(float x, float y, float width, float height, std::string texturePath)
	{
		this->_xPos = x;
		this->_yPos = y;
		this->_width = width;
		this->_height = height;

		this->_buffer = 0;
		this->_texture = ResourcesManager::getTexture(texturePath);

		// Initializing the sprite
		// Creating the buffer if I haven't yet
		if (_buffer == 0)
			glGenBuffers(1, &_buffer);

		//First Triangle
		// Top right
		_vertexData[0].setPosition(_xPos + _width, _yPos + _height);
		_vertexData[0].setUV(1.0f, -1.0f);

		// Top left
		_vertexData[1].setPosition(_xPos, _yPos + _height);
		_vertexData[1].setUV(0.0f, -1.0f);

		// Bottom left
		_vertexData[2].setPosition(_xPos, _yPos);
		_vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		// Bottom left
		_vertexData[3].setPosition(_xPos, _yPos);
		_vertexData[3].setUV(0.0f, 0.0f);

		// Bottom right
		_vertexData[4].setPosition(_xPos + _width, _yPos);
		_vertexData[4].setUV(1.0f, 0.0f);

		// Top right
		_vertexData[5].setPosition(_xPos + _width, _yPos + _height);
		_vertexData[5].setUV(1.0f, -1.0f);

		for (int i = 0; i < 6; i++)
			_vertexData[i].setColor(255, 0, 255, 255);

		_vertexData[2].setColor(0, 0, 255, 255);
		_vertexData[5].setColor(0, 255, 0, 255);

		// Putting the vertex data into the buffer
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexData), _vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Sprite::~Sprite()
	{
		// Cleaning the buffer if I was using it
		if (this->_buffer != 0)
			glDeleteBuffers(1, &_buffer);
	}

	void Sprite::render()
	{
		// OPTIMIZABLE: check if it's already binded
		glBindTexture(GL_TEXTURE_2D, _texture.id);
		// Binding the buffer and sending the vertex data
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);

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