#pragma once

#include <vector>

#include <engine/modules/Text.h>
#include <engine/systems/Renderer.h>
#include <data/RenderData.h>
#include <ui/Glyph.h>
#include <algorithm>

namespace ShyEngine
{
	class TextRenderer : public Renderer<Text, Glyph>
	{
		private:
			std::vector<Text*> m_texts;
			std::vector<Glyph> m_glyphs;
			std::vector<Glyph*> m_glyphPointers;

		public:
			TextRenderer();
			~TextRenderer() {}

			void sortSprites();
			void draw(Text* toDraw);
			void updateModules(ShaderData shaderData);
			void createRenderBatches();
			void addGlyphs(std::vector<Glyph> toAdd);
	};
}