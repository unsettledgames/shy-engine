#pragma once

#include <engine/systems/Renderer.h>
#include <data/SystemData.h>
#include <engine/modules/Sprite.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

// OPTIMIZABLE: use the modulesToUpdate vector to keep track of the glyphs to draw instead of using m_sprites
namespace ShyEngine
{
	class SpriteRenderer : public Renderer<Sprite, Sprite>
	{
		public:
			SpriteRenderer();

			/**
			*	Renders all the sprites in the list of modules to update
			*/
			void updateModules(ShaderData shaderData);
	};
}