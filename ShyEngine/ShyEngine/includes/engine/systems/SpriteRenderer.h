#pragma once

#include <engine/systems/Renderer.h>
#include <data/RenderData.h>
#include <engine/modules/Sprite.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

// OPTIMIZABLE: use the modulesToUpdate vector to keep track of the glyphs to draw
namespace ShyEngine
{
	class SpriteRenderer : public Renderer<Sprite>
	{
		private:

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
			void updateModules(ShaderData shaderData);
	};
}