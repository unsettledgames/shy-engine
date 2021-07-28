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
	public:
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

		Glyph() {}

		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth,
			const GLuint& Texture, const ColorRGBA8& color) : texture(Texture), depth(Depth)
		{
			this->topLeft.color = color;
			this->topRight.color = color;
			this->bottomRight.color = color;
			this->bottomLeft.color = color;

			this->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
			this->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			this->bottomLeft.setPosition(destRect.x, destRect.y);
			this->bottomLeft.setUV(uvRect.x, uvRect.y);

			this->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			this->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

			this->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
			this->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
		}
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
			GLuint _vbo;
			GLuint _vao;
			GlyphSortType _sortType;
			
			// Used for sorting
			std::vector<Glyph*> _glyphPointers;
			// Actual glyphs
			std::vector<Glyph> _glyphs;
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