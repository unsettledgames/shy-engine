#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <rendering/ShaderProgram.h>

#include <data/ColorRGBA8.h>
#include <data/Vertex.h>
#include <data/Texture.h>

// REFACTOR: make Sprite derive from Glyph too

namespace ShyEngine
{
	class Glyph
	{
		template <class ModuleType, class RenderableType>
		friend class Renderer;
		friend bool operator==(const Glyph& e1, const Glyph& e2);

		protected:
			Texture m_texture;
			ShaderProgram m_shader;

			Vertex m_topLeft;
			Vertex m_bottomLeft;
			Vertex m_topRight;
			Vertex m_bottomRight;

			ColorRGBA8 m_color;

			glm::vec2 m_pos;
			glm::vec2 m_scale;
			glm::vec4 m_uv;

			float m_depth;
			unsigned int m_id;

			void init();

		public:
			Glyph() {}
			Glyph(Texture& texture, ShaderProgram& shader, ColorRGBA8 color, float depth);
			Glyph(Texture&& texture, ShaderProgram& shader, ColorRGBA8 color, float depth);
			Glyph(Texture& texture, ShaderProgram& shader, ColorRGBA8 color, glm::vec2 pos, glm::vec2 scale, glm::vec4 uvs, float depth);
			~Glyph() {}

			Texture getTextureId() { return m_texture; }
			float getDepth() { return m_depth; }
			ColorRGBA8 getColor() { return m_color; }
			glm::vec2 getPosition() { return m_pos; }
			glm::vec2 getScale() { return m_scale; }
			glm::vec4 getUV() { return m_uv; }

			void setColor(ColorRGBA8 color) { m_color = color; }
			void setPosition(glm::vec2 pos) { m_pos = pos; }
			void setScale(glm::vec2 scale) { m_scale = scale; }
			void setUV(glm::vec4 uv) { m_uv = uv; }

			void useShader();
			void unuseShader();

			ShaderProgram* getShader() { return &m_shader; }

			/**
			*	Comparison functions used to sort the glyphs
			*/
			static bool compareFrontToBack(Glyph* a, Glyph* b);
			static bool compareBackToFront(Glyph* a, Glyph* b);
			static bool compareTexture(Glyph* a, Glyph* b);
	};
}