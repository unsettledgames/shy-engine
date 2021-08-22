#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <data/Vertex.h>
#include <vector>
#include <algorithm>

namespace ShyEngine
{
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