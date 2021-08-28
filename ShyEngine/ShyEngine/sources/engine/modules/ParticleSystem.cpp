#include <engine/modules/ParticleSystem.h>

namespace ShyEngine
{
	ParticleSystem::~ParticleSystem() {}

	ParticleSystem::ParticleSystem()
	{
		m_transform = (Transform*)m_entity->getModule("Transform");

		init();
	}

	ParticleSystem::ParticleSystem(int maxParticles, std::function<void(Particle& particle)> particleUpdate) : ParticleSystem()
	{
		m_maxParticles = maxParticles;
		m_particleUpdate = particleUpdate;
	}

	void ParticleSystem::init()
	{
		m_particles = new Particle[m_maxParticles];

		m_initialized = true;
	}

	void ParticleSystem::setMaxParticles(unsigned int amount)
	{
		if (m_initialized)
			delete m_particles;

		m_particles = new Particle[amount];
	}

	int ParticleSystem::getFreeParticle()
	{
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++)
		{
			if (m_particles[i].getLifetime() <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		// Free particle was before the last index
		for (int i = 0; i < m_lastFreeParticle; i++)
		{
			if (m_particles[i].getLifetime() <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		// No particles are free, overwrite the first one
		return 0;
	}

	void ParticleSystem::addParticles(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			int lastIndex = getFreeParticle();
			Particle* currParticle = &m_particles[lastIndex];

			currParticle->setPosition(m_transform->getPos());;
			currParticle->setVelocity(m_particleVelocity);
			currParticle->setColor(m_particleColor);
			currParticle->setScale(m_transform->getScale());
			currParticle->setLifetime(1.0f);
		}
	}
}