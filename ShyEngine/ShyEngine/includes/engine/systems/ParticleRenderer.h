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
			ParticleRenderer();
			~ParticleRenderer() {}

			void updateModules(ShaderData& shaderData);
			void draw(std::vector<Particle> toDraw);
	};
}