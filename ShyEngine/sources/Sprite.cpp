#include <Sprite.h>

Sprite::Sprite(float x, float y, float width, float height)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_width = width;
	this->_height = height;

	this->_buffer = 0;

	// Initializing the sprite
	// Vertex data
	float vertexData[12];
	// Creating the buffer if I haven't yet
	if (_buffer == 0)
		glGenBuffers(1, &_buffer);

	// Top left
	vertexData[0] = _xPos - _width / 2;
	vertexData[1] = _yPos - _height / 2;
	// Top right
	vertexData[2] = _xPos + _width / 2;
	vertexData[3] = _yPos + _height / 2;
	// Bottom left
	vertexData[4] = _xPos - _width / 2;
	vertexData[5] = _yPos + _height / 2;

	// Top right
	vertexData[6] = _xPos + _width / 2;
	vertexData[7] = _yPos + _height / 2;
	// Bottom left
	vertexData[8] = _xPos - _width / 2;
	vertexData[9] = _yPos - _height / 2;
	// Bottom right	
	vertexData[10] = _xPos + _width / 2;
	vertexData[11] = _yPos - _height / 2;

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
	// Vertex data
	float vertexData[12];
	// Creating the buffer if I haven't yet
	if (_buffer == 0)
		glCreateBuffers(1, &_buffer);

	// Top left
	vertexData[0] = _xPos - _width / 2;
	vertexData[1] = _yPos - _height / 2;
	// Top right
	vertexData[2] = _xPos + _width / 2;
	vertexData[3] = _yPos - _height / 2;
	// Bottom left
	vertexData[4] = _xPos - _width / 2;
	vertexData[5] = _yPos + _height / 2;

	// Top left
	vertexData[6] = _xPos - _width / 2;
	vertexData[7] = _yPos - _height / 2;
	// Bottom left
	vertexData[8] = _xPos - _width / 2;
	vertexData[9] = _yPos + _height / 2;
	// Bottom right	
	vertexData[10] = _xPos + _width / 2;
	vertexData[11] = _xPos + _height / 2;

	// Binding the buffer and sending the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	// Enabling vertex position
	glEnableVertexAttribArray(0);

	// Apply a shader
	// Draw
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Disabling vertex position
	glDisableVertexAttribArray(0);
	// Unbinding buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}