#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <rendering/ShaderProgram.h>

#include <data/ColorRGBA8.h>
#include <data/Vertex.h>
#include <data/Texture.h>

namespace ShyEngine
{
	class TextRenderer;
	
	class Glyph
	{
		friend bool operator==(const Glyph& e1, const Glyph& e2);
		friend class TextRenderer;

		private:
			Texture m_texture;
			ShaderProgram m_shader;

			Vertex m_topLeft;
			Vertex m_bottomLeft;
			Vertex m_topRight;
			Vertex m_bottomRight;

			ColorRGBA8 m_color;

			glm::vec2 m_pos;
			glm::vec2 m_scale;

			float m_depth;
			char m_character;

			void init();

		public:
			Glyph() {}
			Glyph(char character, Texture& texture, ShaderProgram& shader, ColorRGBA8 color, glm::vec2 pos, glm::vec2 scale, float depth);
			~Glyph() {}

			Texture getTextureId() { return m_texture; }
			float getDepth() { return m_depth; }
			ColorRGBA8 getColor() { return m_color; }

			void useShader();
			void unuseShader();

			ShaderProgram getShader() { return m_shader; }

			/**
			*	Comparison functions used to sort the glyphs
			*/
			static bool compareFrontToBack(Glyph* a, Glyph* b);
			static bool compareBackToFront(Glyph* a, Glyph* b);
			static bool compareTexture(Glyph* a, Glyph* b);
	};
}