#include <data/Particle.h>

namespace ShyEngine
{
	Particle::Particle() : Glyph()
	{
		m_depth = 1.0f;
	}

	Particle::Particle(glm::vec2 pos, glm::vec2 vel, glm::vec2 scale, ColorRGBA8 col, ShaderProgram* shader, Texture& texture, float depth)
		: Glyph(texture, shader, col, depth)
	{
		m_pos = pos;
		m_velocity = vel;
		m_scale = scale;
	}

	void Particle::init(float lifetime, glm::vec4 uvs)
	{
		m_lifetime = lifetime;
		m_uv = uvs;
		m_dead = false;

		updateVertices();
	}
}