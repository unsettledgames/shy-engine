#pragma once

#include <Vertex.h>
#include <cstddef>
#include<GL/glew.h>
#include <Texture.h>
#include <ImageLoader.h>

class Sprite
{
private:
	float _xPos;
	float _yPos;
	float _width;
	float _height;

	Texture _texture;
	Vertex _vertexData[6];

	GLuint _buffer;

public:
	Sprite(float x, float y, float width, float height);

	~Sprite();

	void render();
};