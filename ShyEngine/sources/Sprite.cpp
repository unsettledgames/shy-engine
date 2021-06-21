#include <Sprite.h>

Sprite::Sprite(float x, float y, float width, float height)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_width = width;
	this->_height = height;

	this->_buffer = 0;
	this->_texture = ImageLoader::loadPNG("textures/5heartsSmall.png");

	// Initializing the sprite
	// Creating the buffer if I haven't yet
	if (_buffer == 0)
		glGenBuffers(1, &_buffer);

	// Bottom left
	_vertexData[0].position.x = _xPos - _width / 2;
	_vertexData[0].position.y = _yPos - _height / 2;
	// Top right
	_vertexData[1].position.x = _xPos + _width / 2;
	_vertexData[1].position.y = _yPos + _height / 2;
	// Top left
	_vertexData[2].position.x = _xPos - _width / 2;
	_vertexData[2].position.y = _yPos + _height / 2;

	// Top right
	_vertexData[3].position.x = _xPos + _width / 2;
	_vertexData[3].position.y = _yPos + _height / 2;
	// Bottom left
	_vertexData[4].position.x = _xPos - _width / 2;
	_vertexData[4].position.y = _yPos - _height / 2;
	// Bottom right	
	_vertexData[5].position.x = _xPos + _width / 2;
	_vertexData[5].position.y = _yPos - _height / 2;

	for (int i = 0; i < 6; i++)
	{
		_vertexData[i].color.r = 255;
		_vertexData[i].color.g = 0;
		_vertexData[i].color.b = 255;
		_vertexData[i].color.a = 255;
	}

	_vertexData[2].color.r = 0;
	_vertexData[2].color.g = 0;
	_vertexData[2].color.b = 255;
	_vertexData[2].color.a = 255;

	_vertexData[5].color.r = 0;
	_vertexData[5].color.g = 255;
	_vertexData[5].color.b = 0;
	_vertexData[5].color.a = 255;

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