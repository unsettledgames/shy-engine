#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Vertex.h>
#include <vector>
#include <algorithm>

namespace ShyEngine
{
	class Glyph
	{
		private:
			// REFACTOR: Move to some kind of VectorUtility class or something
			glm::vec2 rotatePoint(glm::vec2 point, float angle);
		public:
			GLuint texture = 0;
			float depth = 0;

			Vertex topLeft;
			Vertex bottomLeft;
			Vertex topRight;
			Vertex bottomRight;

			Glyph() {}

			Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth,
				const GLuint& Texture, const ColorRGBA8& color);

			Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth,
				const GLuint& Texture, const ColorRGBA8& color, float angle);
		
	};

	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class RenderBatch
	{
		private:
		public:
			RenderBatch(GLuint off, GLuint numVertices, GLuint tex) : offset(off), nVertices(numVertices), texture(tex) {}

			GLuint offset;
			GLuint nVertices;
			GLuint texture;
	};

	class SpriteBatch
	{
		private:
			GLuint m_vbo = 0;
			GLuint m_vao = 0;
			GlyphSortType m_sortType = GlyphSortType::TEXTURE;
			
			// Used for sorting
			std::vector<Glyph*> m_glyphPointers;
			// Actual glyphs
			std::vector<Glyph> m_glyphs;
			std::vector<RenderBatch> m_renderBatches;

			void createVertexArray();
			void createRenderBatches();

			void sortGlyphs();
			
			static bool compareFrontToBack(Glyph* a, Glyph* b);
			static bool compareBackToFront(Glyph* a, Glyph* b);
			static bool compareTexture(Glyph* a, Glyph* b);


		public:
			SpriteBatch();

			void init();

			void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

			void end();

			void draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, float depth,
				const GLuint& texture, const ColorRGBA8& color);

			void draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, float depth,
				const GLuint& texture, const ColorRGBA8& color, float angle);

			void draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, float depth,
				const GLuint& texture, const ColorRGBA8& color, glm::vec2 direction);

			void render();
	};
}