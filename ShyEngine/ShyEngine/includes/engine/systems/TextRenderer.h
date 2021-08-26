#pragma once

#include <vector>

#include <engine/modules/Sprite.h>
#include <engine/modules/Text.h>
#include <engine/systems/Renderer.h>
#include <data/RenderData.h>
#include <algorithm>

namespace ShyEngine
{
	class TextRenderer : public Renderer<Text>
	{
		private:
			std::vector<Text*> m_texts;

		public:
			TextRenderer();
			~TextRenderer() {}

			void sortSprites();
			void draw(Text* toDraw);
			void updateModules(ShaderData shaderData);
			void createRenderBatches();
			void addSprites(std::vector<Sprite> toAdd);
	};
}