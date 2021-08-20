#pragma once

#include <engine/System.h>
#include <engine/modules/Sprite.h>
#include <GL/glew.h>

// OPTIMIZABLE: use the modulesToUpdate vector to keep track of the glyphs to draw
namespace ShyEngine
{
	enum class SpriteSortType
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

	class SpriteRenderer : System
	{
		private:
			GLuint m_vbo = 0;
			GLuint m_vao = 0;
			SpriteSortType m_sortType = SpriteSortType::TEXTURE;

			// Used for sorting
			std::vector<Sprite*> m_spritePointers;
			// Actual glyphs
			std::vector<Sprite> m_sprites;
			std::vector<RenderBatch> m_renderBatches;

			void createVertexArray();
			void createRenderBatches();

			void sortSprites();

			static bool compareFrontToBack(Sprite* a, Sprite* b);
			static bool compareBackToFront(Sprite* a, Sprite* b);
			static bool compareTexture(Sprite* a, Sprite* b);
		public:
			SpriteRenderer();
			void init();

			void updateModules();

			void begin(SpriteSortType sortType = SpriteSortType::TEXTURE);

			void draw(Sprite* toDraw);

			void end();

			void render();
	};
}