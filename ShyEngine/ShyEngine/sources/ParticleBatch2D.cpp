#include <ParticleBatch2D.h>

namespace ShyEngine
{
	ParticleBatch2D::~ParticleBatch2D()
	{
		delete m_particles;
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

	void ParticleBatch2D::draw(SpriteBatch batch)
	{
		glm::vec4 destRect;
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

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

				batch.begin();

				batch.draw(destRect, uvRect, m_texture.id, 0, currParticle.m_color);

				batch.end();
				batch.render();

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