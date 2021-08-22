#pragma once

#include <vector>

#include <engine/modules/Text.h>
#include <engine/systems/Renderer.h>
#include <data/RenderData.h>

namespace ShyEngine
{
	class TextRenderer : public Renderer<Text>
	{
		private:

		public:
			TextRenderer() : Renderer<Text>("TextRenderer"){}
			~TextRenderer() {}
	};
}