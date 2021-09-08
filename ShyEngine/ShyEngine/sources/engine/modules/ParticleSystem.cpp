#include <engine/modules/ParticleSystem.h>
#include <data/ResourcesManager.h>

namespace ShyEngine
{
	CLASS_DEFINITION(Module, ParticleSystem);

	ParticleSystem::~ParticleSystem() {}

	ParticleSystem::ParticleSystem(Entity* entity) : Module(entity)
	{
		m_entity = entity;
		m_transform = m_entity->getTransform();
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

	Particle ParticleSystem::updateParticle(int index, float deltaTime)
	{
		if (m_particles[index].m_lifetime > 0)
		{
			m_particleUpdate(m_particles[index], deltaTime * m_simulationSpeed);
			m_particles[index].m_lifetime -= deltaTime * m_simulationSpeed;

			m_particles[index].m_dead = false;
		}
		else
			m_particles[index].m_dead = true;

		return m_particles[index];
	}

	void ParticleSystem::updateSystem(float deltaTime)
	{
		if (m_isPlaying)
		{
			m_particleVelocity = glm::vec2((float)rand() * 5 / RAND_MAX, (float)rand() * 5 / RAND_MAX);
			// Emit particle if needed
			if (m_nextEmissionTime > (1 / m_emissionRate))
			{
				addParticles(std::ceil(m_emissionRate));
				m_nextEmissionTime = 0;
			}

			m_nextEmissionTime += deltaTime;
		}
	}

	void ParticleSystem::updateAll(float deltaTime)
	{
		updateSystem(deltaTime);

		for (int i = 0; i < m_particles.size(); i++)
			updateParticle(i, deltaTime);
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
		m_lastFreeParticle = (m_lastFreeParticle + 1) % m_maxParticles;
		return m_lastFreeParticle;
	}

	void ParticleSystem::addParticles(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			int lastIndex = getFreeParticle();

			m_particles[lastIndex] = Particle::Particle(m_transform->getPos(), m_particleVelocity, 
				m_transform->getScale(), m_particleColor, m_shader, m_texture, 0.0f);
			m_particles[lastIndex].init(m_lifetime, glm::vec4(0, 0, 1, 1));
		}
	}

	std::vector<Particle> ParticleSystem::getParticles()
	{
		return m_particles;
	}
}