#pragma once

#include <string>

#include <engine/Module.h>
#include <ui/SpriteFont.h>

namespace ShyEngine
{
	class Text : public Module
	{
		private:
			SpriteFont* m_spriteFont;
			std::string m_text;

		public:
			Text(Entity* entity, SpriteFont* spriteFont) {}
			Text(Entity* entity, std::string& fontPath, int size) {}
			~Text() {}

			void setText(std::string& text) { m_text = text; }
			std::string getText() { return m_text; }
	};
}