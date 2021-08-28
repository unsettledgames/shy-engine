/**
	PARTICLE:
		- Shouldn't be a single entity
		- Needs a transform
		- Basically a glyph
		- Probably needs some physics stuff (velocity, forces etc)
		- Needs to be updated every frame (it could be seen as a module of the ParticleSystem)
	
	PARTICLE SYSTEM:
		- Renders the particles
		- Updates the properties of the particles
		- Must support adding particles
		
	OPTIONAL PARTICLE ENGINE:
		- Holds all the particle systems and renders them. Could be a system of systems?
	
	OTHER:
		- Let's start with a single ParticleSystem that can be created and registered through the ShyEngine.
		- 

*/



#pragma once

#include <glm/glm.hpp>
#include <data/Vertex.h>
#include <data/Texture.h>
#include <functional>

namespace ShyEngine
{
	class Particle2D
	{
		friend class ParticleBatch2D;

		public:
			glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
			glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
			glm::vec2 m_scale = glm::vec2(1.1f, 1.1f);

			ColorRGBA8 m_color = ColorRGBA8(255, 255, 255, 255);

			float m_lifetime = 0.0f;

	};

	inline void defaultParticleUpdate(Particle2D& particle)
	{
		particle.m_position += particle.m_velocity;
	}

	class ParticleBatch2D
	{
		private:
			Particle2D* m_particles = nullptr;
			Texture m_texture;

			float m_decayRate = 0.1f;

			int m_maxParticles = 1000;
			int m_lastFreeParticle = 0;

			std::function<void(Particle2D& particle)> m_particleUpdate;

			int getFreeParticle();

		public:

			~ParticleBatch2D();

			ParticleBatch2D() {};

			void addParticle(const glm::vec2& position, const ColorRGBA8& color, 
							 const glm::vec2& velocity, const glm::vec2& scale);

			void init(int maxParticles, float decayRate, Texture texture, 
				std::function<void(Particle2D& particle)> updateFunc = defaultParticleUpdate);

			void draw(SpriteBatch* batch);

			void update();

	};
}