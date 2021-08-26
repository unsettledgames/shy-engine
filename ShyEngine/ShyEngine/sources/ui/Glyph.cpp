#include <ui/Glyph.h>
#include <util/Math.h>

namespace ShyEngine
{
	bool Glyph::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->m_depth < b->m_depth;
	}

	bool Glyph::compareBackToFront(Glyph* a, Glyph* b)
	{
		return a->m_depth > b->m_depth;
	}

	bool Glyph::compareTexture(Glyph* a, Glyph* b)
	{
		return a->m_texture.id < b->m_texture.id;
	}

	bool operator==(const Glyph& e1, const Glyph& e2)
	{
		// If a glyph represents the same character, has the same texture id and the same position
		// of another glyph, then the two glyphs are necessarily the same glyphs
		return e1.m_character == e2.m_character && 
			e1.m_texture.id == e2.m_texture.id &&
			e1.m_pos == e2.m_pos;
	}

	Glyph::Glyph(char character, Texture& texture, ShaderProgram& shader, ColorRGBA8 color, glm::vec2 pos, glm::vec2 scale, float depth)
	{
		m_character = character;
		m_texture = texture;
		m_shader = shader;
		m_color = color;
		m_pos = pos;
		m_scale = scale;
		m_depth = depth;

		init();
	}

	// IMPROVABLE: make text rotatable
	void Glyph::init()
	{
		// Get the corners
		glm::vec2 halfSize(m_scale.x / 2.0f, m_scale.y / 2.0f);
		glm::vec2 topLeft(0, m_scale.y);
		glm::vec2 topRight(m_scale.x, m_scale.y);
		glm::vec2 bottomRight(m_scale.x, 0);
		glm::vec2 bottomLeft(m_scale.x, 0);

		this->m_topLeft.color = m_color;
		this->m_topRight.color = m_color;
		this->m_bottomRight.color = m_color;
		this->m_bottomLeft.color = m_color;

		// UV = (0, 0, 1, -1);
		this->m_topLeft.setPosition(m_pos.x + topLeft.x, m_pos.y + topLeft.y);
		this->m_topLeft.setUV(0, -1);

		this->m_bottomLeft.setPosition(m_pos.x + bottomLeft.x, m_pos.y + bottomLeft.y);
		this->m_bottomLeft.setUV(0, 0);

		this->m_topRight.setPosition(m_pos.x + topRight.x, m_pos.y + topRight.y);
		this->m_topRight.setUV(1, -1);

		this->m_bottomRight.setPosition(m_pos.x + bottomRight.x, m_pos.y + bottomRight.y);
		this->m_bottomRight.setUV(1, 0);
	}

	void Glyph::useShader()
	{
		m_shader.use(SDL_GetTicks());
	}

	void Glyph::unuseShader()
	{
		m_shader.unuse();
	}
}