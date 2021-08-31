#include <engine/modules/ParticleSystem.h>
#include <data/ResourcesManager.h>

namespace ShyEngine
{
	ParticleSystem::~ParticleSystem() {}

	ParticleSystem::ParticleSystem(Entity* entity) : Module("ParticleSystem", entity)
	{
		m_entity = entity;
		m_transform = (Transform*)m_entity->getModule("Transform");

		init();
	}

	ParticleSystem::ParticleSystem(Entity* entity, int maxParticles, Texture texture, ShaderProgram* shader,
		std::function<void(Particle& particle, float deltaTime)> particleUpdate) : ParticleSystem(entity)
	{
		m_texture = texture;
		m_maxParticles = maxParticles;
		m_particleUpdate = particleUpdate;
		m_shader = shader;
	}

	ParticleSystem::ParticleSystem(Entity* entity, int maxParticles, std::string& texture, ShaderProgram* shader,
		std::function<void(Particle& particle, float deltaTime)> particleUpdate /*= defaultParticleUpdate*/) :
		ParticleSystem(entity, maxParticles, ResourcesManager.getTexture(texture), shader, particleUpdate) {}
	ParticleSystem::ParticleSystem(Entity* entity, int maxParticles, std::string&& texture, ShaderProgram* shader,
		std::function<void(Particle& particle, float deltaTime)> particleUpdate /*= defaultParticleUpdate*/) :
		ParticleSystem(entity, maxParticles, ResourcesManager.getTexture(texture), shader, particleUpdate) {}

	void ParticleSystem::init()
	{
		m_particles.reserve(m_maxParticles);

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

				std::printf("N particles: %d\n", m_particles.size());
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
		Particle* currParticle;

		for (int i = 0; i < amount; i++)
		{
			if (m_particles.size() > 0)
			{
				int lastIndex = getFreeParticle();

				currParticle = &m_particles[lastIndex];
			}
			else
			{
				Particle added;

				m_particles.push_back(added);
				currParticle = &m_particles[0];
			}

			currParticle->m_pos = m_transform->getPos();
			currParticle->m_velocity = m_particleVelocity;
			currParticle->m_color = m_particleColor;
			currParticle->m_scale = m_transform->getScale();
			currParticle->m_lifetime = m_lifetime;
			currParticle->m_shader = m_shader;
			currParticle->m_texture = m_texture;
		}
	}

	std::vector<Particle> ParticleSystem::getParticles()
	{
		return m_particles;
	}
}