#include <data/Glyph.h>
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
		return (a->m_texture.id < b->m_texture.id);
	}

	bool Glyph::compareShaderTexture(Glyph* a, Glyph* b)
	{
		return (a->getShader()->getId() == b->getShader()->getId() ? Glyph::compareTexture(a, b) : a->getShader()->getId() < b->getShader()->getId());
	}

	bool operator==(const Glyph& e1, const Glyph& e2)
	{
		return e1.m_id == e2.m_id;
	}

	Glyph::Glyph(Texture&& texture, ShaderProgram* shader, ColorRGBA8 color, float depth)
	{
		m_texture = texture;
		m_shader = shader;
		m_color = color;
		m_depth = depth;

		updateVertices();
	}

	Glyph::Glyph(Texture& texture, ShaderProgram* shader, ColorRGBA8 color, float depth)
	{
		m_texture = texture;
		m_shader = shader;
		m_color = color;
		m_depth = depth;

		updateVertices();
	}

	Glyph::Glyph(Texture& texture, ShaderProgram* shader, ColorRGBA8 color, glm::vec2 pos, glm::vec2 scale, glm::vec4 uv, float depth)
	{
		m_texture = texture;
		m_shader = shader;
		m_color = color;
		m_pos = pos;
		m_scale = scale;
		m_depth = depth;
		m_uv = uv;

		updateVertices();
	}

	// IMPROVABLE: make text rotatable
	void Glyph::updateVertices()
	{
		// Set the corners
		glm::vec2 topLeft(-m_scale.x / 2, m_scale.y / 2);
		glm::vec2 topRight(m_scale.x / 2, m_scale.y / 2);
		glm::vec2 bottomRight(m_scale.x / 2, -m_scale.y / 2);
		glm::vec2 bottomLeft(-m_scale.x / 2, -m_scale.y / 2);

		// Set the color of each corner
		this->m_topLeft.color = m_color;
		this->m_topRight.color = m_color;
		this->m_bottomRight.color = m_color;
		this->m_bottomLeft.color = m_color;

		/*
			UV:
			(x, y) -> coordinates of the bottom left corner
			(z, w) -> uv scale

			bottom left: x, y
			bottom right: x + z, y
			top left: x, y + w
			top right: x + z, y + w
		*/
		// UV = (0, 0, 1, -1);
		this->m_topLeft.setPosition(m_pos.x + topLeft.x, m_pos.y + topLeft.y);
		this->m_topLeft.setUV(m_uv.x, m_uv.y - m_uv.w);

		this->m_bottomLeft.setPosition(m_pos.x + bottomLeft.x, m_pos.y + bottomLeft.y);
		this->m_bottomLeft.setUV(m_uv.x, m_uv.y);

		this->m_topRight.setPosition(m_pos.x + topRight.x, m_pos.y + topRight.y);
		this->m_topRight.setUV(m_uv.x + m_uv.z, m_uv.y - m_uv.w);

		this->m_bottomRight.setPosition(m_pos.x + bottomRight.x, m_pos.y + bottomRight.y);
		this->m_bottomRight.setUV(m_uv.x + m_uv.z, m_uv.y);
	}

	void Glyph::useShader()
	{
		m_shader->use(SDL_GetTicks());
	}

	void Glyph::unuseShader()
	{
		m_shader->unuse();
	}

	void Glyph::setColor(ColorRGBA8 color)
	{
		m_color = color;

		m_topLeft.color = color;
		m_bottomLeft.color = color;
		m_bottomRight.color = color;
		m_topRight.color = color;
	}

	void Glyph::setPosition(glm::vec2 pos)
	{
		m_pos = pos;
		updateVertices();
	}

	void Glyph::setScale(glm::vec2 scale)
	{
		m_scale = scale;
		updateVertices();
	}
}