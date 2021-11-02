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
			// Texture and shader used to render the glyph
			Texture m_texture;
			ShaderProgram* m_shader;

			// Vertex data
			Vertex m_topLeft;
			Vertex m_bottomLeft;
			Vertex m_topRight;
			Vertex m_bottomRight;

			// Color
			ColorRGBA8 m_color;

			// Position, scale and uvs
			glm::vec2 m_pos;
			glm::vec2 m_scale;
			glm::vec4 m_uv;

			// Sorting depth (UNUSED at the moment) and glyph id, used to compare Glyphs
			float m_depth;
			unsigned int m_id;

		public:
			Glyph() {}
			Glyph(Texture& texture, ShaderProgram* shader, ColorRGBA8 color, float depth);
			Glyph(Texture&& texture, ShaderProgram* shader, ColorRGBA8 color, float depth);
			Glyph(Texture& texture, ShaderProgram* shader, ColorRGBA8 color, glm::vec2 pos, glm::vec2 scale, glm::vec4 uvs, float depth);
			~Glyph() {}
			
			/*
				\brief	Updates the vertices depending on the position and scale of the glyph
			*/
			void updateVertices();

			Texture getTextureId() { return m_texture; }
			float getDepth() { return m_depth; }
			ColorRGBA8 getColor() { return m_color; }
			glm::vec2 getPosition() { return m_pos; }
			glm::vec2 getScale() { return m_scale; }
			glm::vec4 getUV() { return m_uv; }
			ShaderProgram* getShader() { return m_shader; }

			void setColor(ColorRGBA8 color);
			void setPosition(glm::vec2 pos);
			// REFACTOR: reimplement this in Glyph.cpp so that they update the vertices
			void setScale(glm::vec2 scale);
			void setUV(glm::vec4 uv) { m_uv = uv; }

			/*
				\brief Setup SDL to use the shader attached to the glyph
			*/
			void useShader();

			/*
				\brief Setup SDL to stop using the shader attached to the glyph
			*/
			void unuseShader();

			/**
			*	Comparison functions used to sort the glyphs
			*/
			static bool compareFrontToBack(Glyph* a, Glyph* b);
			static bool compareBackToFront(Glyph* a, Glyph* b);
			static bool compareTexture(Glyph* a, Glyph* b);
			static bool compareShaderTexture(Glyph* a, Glyph* b);
			
	};
}