#pragma once

#include <glm/glm.hpp>
#include <Vertex.h>
#include <SpriteBatch.h>
#include <Texture.h>

namespace ShyEngine
{
	class Particle2D
	{
		friend class ParticleBatch2D;

		private:
			glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
			glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
			glm::vec2 m_scale = glm::vec2(1.1f, 1.1f);

			ColorRGBA8 m_color = ColorRGBA8(255, 255, 255, 255);

			float m_lifetime = 0.0f;

			void update();

	};

	class ParticleBatch2D
	{
		private:
			Particle2D* m_particles = nullptr;
			Texture m_texture;

			float m_decayRate = 0.1f;

			int m_maxParticles;

			void update();


		public:

			~ParticleBatch2D();

			ParticleBatch2D();

			void addParticle(const glm::vec2& position, const ColorRGBA8& color, const glm::vec2& velocity);

			void init(int maxParticles, float decayRate, Texture texture);

			void draw(SpriteBatch batch);

	};
}