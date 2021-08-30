#pragma once

#include <functional>

#include <data/Particle.h>
#include <data/Texture.h>
#include <data/ColorRGBA8.h>

#include <engine/Entity.h>
#include <engine/modules/Transform.h>
#include <engine/Module.h>

// REFACTOR: try to think more about what the update function should do. Is a user defined function really needed?
// Isn't it better to let the user create animations and set the parameters then leave the rest to the engine?

namespace ShyEngine
{
	inline void defaultParticleUpdate(Particle& particle, float deltaTime)
	{
		particle.setPosition(particle.getPosition() + particle.getVelocity() * deltaTime);
	}

	class ParticleSystem : public Module
	{
		private:
			Transform* m_transform;
			std::vector<Particle> m_particles;
			Texture m_texture;

			// Particle System parameters
			float m_maxParticles = 1.0f;
			float m_simulationSpeed = 1.0f;

			// Parameters per particle
			glm::vec2 m_particleVelocity = glm::vec2(1, 1);
			ColorRGBA8 m_particleColor = ColorRGBA8(255, 255, 255, 255);

			bool m_initialized = false;
			unsigned int m_lastFreeParticle = 0;

			std::function<void(Particle& particle, float deltaTime)> m_particleUpdate;

			void init();
			int getFreeParticle();
		public:
			ParticleSystem();
			ParticleSystem(int maxParticles, std::function<void(Particle& particle, float deltaTime)> particleUpdate = defaultParticleUpdate);
			~ParticleSystem();

			void addParticles(int amount);

			float getMaxParticles() { return m_maxParticles; }
			void setMaxParticles(unsigned int amount);

			void update(float deltaTime);
			std::vector<Particle> getParticles();
	};
}