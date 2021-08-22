#include <ui/Glyph.h>

namespace ShyEngine
{
	Glyph::Glyph(char character, GLuint texture, glm::vec4 uv, glm::vec4 rect, float depth, ColorRGBA8 col)
	{
		m_character = character;
		m_texture = texture;
		m_uv = uv;
		m_destRect = rect;
		m_depth = depth;
		m_color = col;
	}
}