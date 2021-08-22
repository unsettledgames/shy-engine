#pragma once

#include <vector>

#include <ui/Glyph.h>
#include <engine/modules/Text.h>
#include <engine/systems/Renderer.h>
#include <data/RenderData.h>

namespace ShyEngine
{
	class TextRenderer : public Renderer<Glyph>
	{
		private:

		public:
			TextRenderer() : Renderer<Text>("TextRenderer"){}
			~TextRenderer() {}

			void sortSprites();
			bool compareFrontToBack(Glyph* a, Glyph* b);
			bool compareBackToFront(Glyph* a, Glyph* b);
			bool compareTexture(Glyph* a, Glyph* b);
	};
}