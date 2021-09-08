#pragma once

#include <vector>
#include <engine/modules/Text.h>
#include <engine/systems/Renderer.h>
#include <data/SystemData.h>
#include <data/Glyph.h>
#include <algorithm>

namespace ShyEngine
{
	class TextRenderer : public Renderer<Text, Glyph>
	{
		private:

		public:
			TextRenderer();
			~TextRenderer() {}

			void draw(Text* toDraw, ShaderData shaderData);
			void updateModules(ShaderData shaderData);
			void addGlyphs(std::vector<Glyph> toAdd, ShaderData shaderData);
	};
}