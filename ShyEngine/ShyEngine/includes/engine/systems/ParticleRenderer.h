#pragma once

#include <functional>
#include <vector>

#include <engine/systems/Renderer.h>
#include <engine/modules/ParticleSystem.h>

#include <data/Particle.h>

namespace ShyEngine
{
	class ParticleRenderer : public Renderer<ParticleSystem, Particle>
	{
		private:

		public:
			ParticleRenderer() : Renderer<ParticleSystem, Particle>("ParticleRenderer") {};
			~ParticleRenderer() {}

			void updateModules();
			void draw(std::vector<Particle> toDraw);
	};
}