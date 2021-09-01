#include <engine/modules/ParticleSystem.h>
#include <data/ResourcesManager.h>

namespace ShyEngine
{
	ParticleSystem::~ParticleSystem() {}

	ParticleSystem::ParticleSystem(Entity* entity) : Module("ParticleSystem", entity)
	{
		m_entity = entity;
		m_transform = (Transform*)m_entity->getModule("Transform");
		m_lifetime = 1.0f;
		m_maxParticles = 100;
	}

	ParticleSystem::ParticleSystem(Entity* entity, int maxParticles, Texture texture, ShaderProgram* shader,
		std::function<void(Particle& particle, float deltaTime)> particleUpdate) : ParticleSystem(entity)
	{
		m_texture = texture;
		m_maxParticles = maxParticles;
		m_particleUpdate = particleUpdate;
		m_shader = shader;

		init();
	}

	ParticleSystem::ParticleSystem(Entity* entity, int maxParticles, std::string& texture, ShaderProgram* shader,
		std::function<void(Particle& particle, float deltaTime)> particleUpdate /*= defaultParticleUpdate*/) :
		ParticleSystem(entity, maxParticles, ResourcesManager.getTexture(texture), shader, particleUpdate) {}
	ParticleSystem::ParticleSystem(Entity* entity, int maxParticles, std::string&& texture, ShaderProgram* shader,
		std::function<void(Particle& particle, float deltaTime)> particleUpdate /*= defaultParticleUpdate*/) :
		ParticleSystem(entity, maxParticles, ResourcesManager.getTexture(texture), shader, particleUpdate) {}

	void ParticleSystem::init()
	{
		m_particles.resize(m_maxParticles);
		m_initialized = true;
		play();
	}

	void ParticleSystem::play()
	{
		m_isPlaying = true;
	}

	void ParticleSystem::stop(bool destroyParticles /*= false*/)
	{
		m_isPlaying = false;

		if (destroyParticles)
			m_particles.clear();
	}

	void ParticleSystem::update(float deltaTime)
	{
		if (m_isPlaying)
		{
			// Emit particle if needed
			if (m_nextEmissionTime > (1 / m_emissionRate))
			{
				addParticles(m_emissionRate);
				m_nextEmissionTime = 0;
			}

			for (int i = 0; i < m_maxParticles && i < m_particles.size(); i++)
			{
				// Check if the particle is active
				if (m_particles[i].m_lifetime > 0.0f)
				{
					m_particleUpdate(m_particles[i], deltaTime * m_simulationSpeed);
					m_particles[i].m_lifetime -= deltaTime * m_simulationSpeed;
				}
			}

			m_nextEmissionTime += deltaTime;
		}
	}

	void ParticleSystem::setMaxParticles(unsigned int amount)
	{
		m_particles.clear();
		m_particles.reserve(amount);
	}

	int ParticleSystem::getFreeParticle()
	{
		for (int i = m_lastFreeParticle; i<m_maxParticles && i<m_particles.size(); i++)
		{
			if (m_particles[i].getLifetime() <= 0.0f)
			{
				m_lastFreeParticle = (i + 1) % 1000;
				return i;
			}
		}

		// Free particle was before the last index
		for (int i = 0; i < m_lastFreeParticle; i++)
		{
			if (m_particles[i].getLifetime() <= 0.0f)
			{
				m_lastFreeParticle = (i+1) % 1000;
				return i;
			}
		}

		// No particles are free, overwrite the next one
		m_lastFreeParticle = (m_lastFreeParticle + 1) % 1000;
		return m_lastFreeParticle;
	}

	void ParticleSystem::addParticles(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			int lastIndex = getFreeParticle();

			m_particles[lastIndex].m_pos = m_transform->getPos();
			m_particles[lastIndex].m_velocity = m_particleVelocity;
			m_particles[lastIndex].m_color = m_particleColor;
			m_particles[lastIndex].m_scale = m_transform->getScale();
			m_particles[lastIndex].m_lifetime = m_lifetime;
			m_particles[lastIndex].m_shader = m_shader;
			m_particles[lastIndex].m_texture = m_texture;
		}
	}

	std::vector<Particle> ParticleSystem::getParticles()
	{
		return m_particles;
	}
}