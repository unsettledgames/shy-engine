#pragma once

#include <functional>

#include <engine/systems/Renderer.h>
#include <engine/modules/ParticleSystem.h>

#include <data/Particle.h>

namespace ShyEngine
{
	inline void defaultParticleUpdate(Particle& particle)
	{
		particle.setPosition(particle.getPosition() + particle.getVelocity());
	}

	class ParticleRenderer : Renderer<ParticleSystem, Particle>
	{
		private:
			

		public:
			
	};
}