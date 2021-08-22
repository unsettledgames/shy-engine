#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <data/ColorRGBA8.h>

namespace ShyEngine
{
	class Glyph
	{
		private:
			char m_character;
			GLuint m_texture;

			glm::vec4 m_uv;
			glm::vec4 m_destRect;

			float m_depth;
			ColorRGBA8 m_color;

		public:
			Glyph();
			~Glyph();
			Glyph(char character, GLuint texture, glm::vec4 uv, glm::vec4 rect, float depth, ColorRGBA8 col);

			char getChar() { return m_character; }
			GLuint getTextureId() { return m_texture; }
			glm::vec4 getUv() { return m_uv; }
			glm::vec4 getDestRect() { return m_destRect; }
			float getDepth() { return m_depth; }
			ColorRGBA8 getColor() { return m_color; }
	};
}