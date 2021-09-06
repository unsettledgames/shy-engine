#pragma once

#include <data/Glyph.h>
#include <glm/glm.hpp>

namespace ShyEngine
{
	class ParticleSystem;
	class ParticleRenderer;

	class Particle : public Glyph
	{
		friend class ParticleSystem;
		friend class ParticleRenderer;

		private:
			glm::vec2 m_velocity = glm::vec2(0, 0);
			float m_lifetime = 0.0f;
			bool m_dead = true;
		public:
			Particle();
			Particle(glm::vec2 pos, glm::vec2 vel, glm::vec2 scale, ColorRGBA8 col, ShaderProgram* shader,
				Texture& texture, float depth);
			~Particle() {};

			void init(float lifetime, glm::vec4 uvs);

			float getLifetime() { return m_lifetime; }
			void setLifetime(float lifetime) { m_lifetime = lifetime; }
			
			glm::vec2 getVelocity() { return m_velocity; }
			void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	};
}