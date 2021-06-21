#include <Sprite.h>

Sprite::Sprite(float x, float y, float width, float height)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_width = width;
	this->_height = height;

	this->_buffer = 0;

	// Initializing the sprite
	// Creating the buffer if I haven't yet
	if (_buffer == 0)
		glGenBuffers(1, &_buffer);

	// Bottom left
	vertexData[0].position.x = _xPos - _width / 2;
	vertexData[0].position.y = _yPos - _height / 2;
	// Top right
	vertexData[1].position.x = _xPos + _width / 2;
	vertexData[1].position.y = _yPos + _height / 2;
	// Top left
	vertexData[2].position.x = _xPos - _width / 2;
	vertexData[2].position.y = _yPos + _height / 2;

	// Top right
	vertexData[3].position.x = _xPos + _width / 2;
	vertexData[3].position.y = _yPos + _height / 2;
	// Bottom left
	vertexData[4].position.x = _xPos - _width / 2;
	vertexData[4].position.y = _yPos - _height / 2;
	// Bottom right	
	vertexData[5].position.x = _xPos + _width / 2;
	vertexData[5].position.y = _yPos - _height / 2;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[2].color.r = 0;
	vertexData[2].color.g = 0;
	vertexData[2].color.b = 255;
	vertexData[2].color.a = 255;

	vertexData[5].color.r = 0;
	vertexData[5].color.g = 255;
	vertexData[5].color.b = 0;
	vertexData[5].color.a = 255;

	// Putting the vertex data into the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
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
	// Binding the buffer and sending the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	// Enabling vertex position
	glEnableVertexAttribArray(0);

	// Bind position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// Bind color attribute
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Disabling vertex position
	glDisableVertexAttribArray(0);
	// Unbinding buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}