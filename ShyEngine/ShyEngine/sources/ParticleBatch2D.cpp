#include <ParticleBatch2D.h>

namespace ShyEngine
{
	ParticleBatch2D::~ParticleBatch2D()
	{
		delete m_particles;
	}

	int ParticleBatch2D::getFreeParticle()
	{
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++)
		{
			if (m_particles[i].m_lifetime <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		// Free particle was before the last index
		for (int i = 0; i < m_lastFreeParticle; i++)
		{
			if (m_particles[i].m_lifetime <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		// No particles are free, overwrite the first one
		return 0;
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position, const ColorRGBA8& color,
		const glm::vec2& velocity, const glm::vec2& scale)
	{
		int lastIndex = getFreeParticle();
		Particle2D* currParticle = &m_particles[lastIndex];

		currParticle->m_position = position;
		currParticle->m_velocity = velocity;
		currParticle->m_color = color;
		currParticle->m_scale = scale;
		currParticle->m_lifetime = 1.0f;
	}

	void ParticleBatch2D::init(int maxParticles, float decayRate, Texture texture)
	{
		m_maxParticles = maxParticles;
		m_decayRate = decayRate;
		m_texture = texture;

		m_particles = new Particle2D[m_maxParticles];
	}

	void ParticleBatch2D::update()
	{
		for (int i = 0; i < m_maxParticles; i++)
		{
			// Check if the particle is active
			if (m_particles[i].m_lifetime > 0.0f)
			{
				m_particles[i].update();
				m_particles[i].m_lifetime -= m_decayRate;
			}
		}
	}

	void ParticleBatch2D::draw(SpriteBatch* batch)
	{
		glm::vec4 destRect;
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, -1.0f);

		for (int i = 0; i < m_maxParticles; i++)
		{
			// Check if the particle is active
			if (m_particles[i].m_lifetime > 0.0f)
			{
				Particle2D currParticle = m_particles[i];

				destRect.x = currParticle.m_position.x;
				destRect.y = currParticle.m_position.y;
				destRect.z = currParticle.m_scale.x;
				destRect.w = currParticle.m_scale.y;

				batch->begin();

				batch->draw(destRect, uvRect, 1, m_texture.id, currParticle.m_color);

				batch->end();
				batch->render();

				m_particles[i].update();
				m_particles[i].m_lifetime -= m_decayRate;
			}
		}
	}

	void Particle2D::update()
	{
		// TODO: use delta time
		m_position += m_velocity;
	}
}