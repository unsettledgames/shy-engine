#pragma once

#include <functional>

#include <data/Particle.h>
#include <data/Texture.h>
#include <data/ColorRGBA8.h>

#include <engine/Entity.h>
#include <engine/modules/Transform.h>
#include <engine/Module.h>

namespace ShyEngine
{
	class ParticleSystem : Module
	{
		private:
			Transform* m_transform;
			Particle* m_particles;
			Texture m_texture;

			// Particle System parameters
			float m_maxParticles = 1.0f;
			float m_simulationSpeed = 1.0f;

			// Parameters per particle
			glm::vec2 m_particleVelocity = glm::vec2(1, 1);
			ColorRGBA8 m_particleColor = ColorRGBA8(255, 255, 255, 255);

			bool m_initialized = false;
			unsigned int m_lastFreeParticle = 0;

			std::function<void(Particle& particle)> m_particleUpdate;

			void init();
			int getFreeParticle();
		public:
			ParticleSystem();
			ParticleSystem(int maxParticles, std::function<void(Particle& particle)> particleUpdate);
			~ParticleSystem();

			void addParticles(int amount);

			float getMaxParticles() { return m_maxParticles; }
			void setMaxParticles(unsigned int amount);
	};
}