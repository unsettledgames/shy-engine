#pragma once

#include <functional>
#include <string>
#include <glm/glm.hpp>
#include <util/Classes.h>

#include <rendering/ShaderProgram.h>

#include <data/Particle.h>
#include <data/Texture.h>
#include <data/ColorRGBA8.h>

#include <engine/Entity.h>
#include <engine/modules/Transform.h>
#include <engine/Module.h>

// REFACTOR: try to think more about what the update function should do. Is a user defined function really needed?
// Isn't it better to let the user create animations and set the parameters then leave the rest to the engine?

// REFACTOR: m_maxParticles should be an int

namespace ShyEngine
{
	inline void defaultParticleUpdate(Particle& particle, float deltaTime)
	{
		particle.setPosition(particle.getPosition() + particle.getVelocity() * deltaTime);
	}

	class ParticleSystem : public Module
	{
		CLASS_DECLARATION(ParticleSystem);
		class ParticleRenderer;
		friend class ParticleRenderer;

		private:
			ShaderProgram* m_shader;
			Transform* m_transform;
			std::vector<Particle> m_particles;
			Texture m_texture;

			// Particle System parameters
			int m_maxParticles = 1;
			float m_simulationSpeed = 1.0f;
			float m_emissionRate = 1.0f;

			// Parameters per particle
			float m_lifetime;
			glm::vec2 m_particleVelocity = glm::vec2((float)rand()*5 / RAND_MAX, (float)rand()*5 / RAND_MAX);
			ColorRGBA8 m_particleColor = ColorRGBA8(255, 255, 255, 255);

			// State
			bool m_initialized = false;
			bool m_isPlaying = false;
			float m_nextEmissionTime = 0.0f;
			unsigned int m_lastFreeParticle = 0;

			std::function<void(Particle& particle, float deltaTime)> m_particleUpdate;

			void init();
			int getFreeParticle();
		public:
			ParticleSystem() {}

			ParticleSystem(Entity* entity);

			ParticleSystem(Entity* entity, int maxParticles, std::string& texture, ShaderProgram* shader,
				std::function<void(Particle& particle, float deltaTime)> particleUpdate = defaultParticleUpdate);
			ParticleSystem(Entity* entity, int maxParticles, std::string&& texture, ShaderProgram* shader,
				std::function<void(Particle& particle, float deltaTime)> particleUpdate = defaultParticleUpdate);

			ParticleSystem(Entity* entity, int maxParticles, Texture texture, ShaderProgram* shader,
				std::function<void(Particle& particle, float deltaTime)> particleUpdate = defaultParticleUpdate);
			
			~ParticleSystem();

			void addParticles(int amount);

			float getMaxParticles() { return m_maxParticles; }
			void setMaxParticles(unsigned int amount);

			float getLifetime() { return m_lifetime; }
			void setLifetime(float lifetime) { m_lifetime = lifetime; }

			float getEmissionRate() { return m_emissionRate; }
			void setEmissionRate(float emissionRate) { m_emissionRate = emissionRate; }

			void play();
			void stop(bool destroyParticles = false);

			void updateAll(float deltaTime);
			void updateSystem(float deltaTime);
			Particle updateParticle(int index, float deltaTime);

			std::vector<Particle> getParticles();
	};
}