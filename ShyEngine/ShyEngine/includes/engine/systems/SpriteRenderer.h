#pragma once

#include <engine/systems/Renderer.h>
#include <data/RenderData.h>
#include <engine/modules/Sprite.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

// OPTIMIZABLE: use the modulesToUpdate vector to keep track of the glyphs to draw instead of using m_sprites
namespace ShyEngine
{
	class SpriteRenderer : public Renderer<Sprite, Sprite>
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

		public:
			SpriteRenderer();

			/**
			*	Renders all the sprites in the list of modules to update
			*/
			void updateModules(ShaderData shaderData);
	};
}