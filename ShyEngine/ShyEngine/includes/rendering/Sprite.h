#pragma once

#include <data/Vertex.h>
#include <cstddef>
#include<GL/glew.h>
#include <data/Texture.h>
#include <data/ImageLoader.h>
#include <data/ResourcesManager.h>

namespace ShyEngine {
	class Sprite
	{
	private:
		float m_xPos;
		float m_yPos;
		float m_width;
		float m_height;

		Texture m_texture;
		Vertex m_vertexData[6];
		GLuint m_buffer;

	public:
		Sprite(float x, float y, float width, float height, std::string texturePath);

		~Sprite();

		void render();
	};
}