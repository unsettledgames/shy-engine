#pragma once

#include <engine/System.h>
#include <engine/modules/Sprite.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

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

	class SpriteRenderer : public System
	{
		private:
			// Sprites to render
			std::vector<Sprite> m_modulesToUpdate;

			// Vertex buffer object
			GLuint m_vbo = 0;
			// Vertex attribute object
			GLuint m_vao = 0;
			// Tells how to sort the sprites
			SpriteSortType m_sortType = SpriteSortType::TEXTURE;

			// Used for sorting
			std::vector<Sprite*> m_spritePointers;
			// Actual sprites
			std::vector<Sprite> m_sprites;
			// List of batches
			std::vector<RenderBatch> m_renderBatches;

			/**
			*	Creates the vertex arrays, binds the attributes 
			*/
			void createVertexArray();

			/**
			*	Creates the batches given the sprites that must be drawn. Groups sprites with the same
			*	texture into a single batch, must be called after sortSprites
			*/
			void createRenderBatches();

			/**
			*	Sorts the sprites depending on their texture
			*/
			void sortSprites();

			/**
			*	Comparison functions used to sort the sprites
			*/
			static bool compareFrontToBack(Sprite* a, Sprite* b);
			static bool compareBackToFront(Sprite* a, Sprite* b);
			static bool compareTexture(Sprite* a, Sprite* b);

		public:
			SpriteRenderer();

			/**
			*	Renders all the sprites in the list of modules to update
			*/
			void updateModules(glm::mat4 cameraMatrix);

			/**
			*	Marks the beginning of a rendering phase. Sets the sort type, initializes the process.
			*/
			void begin(SpriteSortType sortType = SpriteSortType::TEXTURE);

			/**
			*	Adds a sprite to the list of sprites to be drawn.
			*/
			void draw(Sprite* toDraw);

			/**
			*	Marks the end of a rendering phase: sorts the sprites and creates the batches.
			*/
			void end();

			/**
			*	Renders all the sprites
			*/
			void render();

			void addModule(Sprite toAdd);
	};
}