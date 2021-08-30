#pragma once

#include <data/Glyph.h>
#include <glm/glm.hpp>

namespace ShyEngine
{
	class ParticleSystem;

	class Particle : public Glyph
	{
		friend class ParticleSystem;

		private:
			glm::vec2 m_velocity = glm::vec2(0, 0);
			float m_lifetime = 0.0f;
		public:
			Particle() {};
			~Particle() {};

			float getLifetime() { return m_lifetime; }
			void setLifetime(float lifetime) { m_lifetime = lifetime; }
			
			glm::vec2 getVelocity() { return m_velocity; }
			void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	};
}