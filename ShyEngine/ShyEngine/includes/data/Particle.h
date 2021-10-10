#pragma once

#include <data/Glyph.h>
#include <glm/glm.hpp>

namespace ShyEngine
{
	class ParticleSystem;
	class ParticleRenderer;

	/*
		\brief	Represents a particle to be used in ParticleSystems.

		Most of the rendering-related functions and data are defined in Glyph, from which Particle derives.
		In addition, Particle contains data that is updated by the ParticleSystem (for example the velocity
		or the lifetime).
	*/
	class Particle : public Glyph
	{
		friend class ParticleSystem;
		friend class ParticleRenderer;

		private:
			// Particle velocity
			glm::vec2 m_velocity = glm::vec2(0, 0);
			// Particle lifetime (in milliseconds): when it expires, the particle is destroyed
			float m_lifetime = 0.0f;
			// Tells whether or not the particle should be destroyed
			bool m_dead = true;
		public:
			Particle();
			Particle(glm::vec2 pos, glm::vec2 vel, glm::vec2 scale, ColorRGBA8 col, ShaderProgram* shader,
				Texture& texture, float depth);
			~Particle() {};

			/*
				\brief Initializes the particle by setting the right attributes and by updating the vertices accordingly
			*/
			void init(float lifetime, glm::vec4 uvs);

			float getLifetime() { return m_lifetime; }
			void setLifetime(float lifetime) { m_lifetime = lifetime; }
			
			glm::vec2 getVelocity() { return m_velocity; }
			void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	};
}