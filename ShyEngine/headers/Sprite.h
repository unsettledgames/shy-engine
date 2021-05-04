#pragma once

#include<GL/glew.h>

class Sprite
{
private:
	float _xPos;
	float _yPos;
	float _width;
	float _height;

	GLuint _buffer;

public:
	Sprite(float x, float y, float width, float height);

	~Sprite();

	void render();
};