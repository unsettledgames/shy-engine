#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Vertex.h>
#include <vector>
#include <algorithm>

namespace ShyEngine
{
	typedef struct glyph
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	} Glyph;

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
			GLuint _vbo;
			GLuint _vao;
			GlyphSortType _sortType;

			std::vector<Glyph*> _glyphs;
			std::vector<RenderBatch> _renderBatches;

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

			void render();
	};
}