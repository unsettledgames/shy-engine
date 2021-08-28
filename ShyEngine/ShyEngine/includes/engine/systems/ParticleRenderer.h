#pragma once

#include <engine/systems/Renderer.h>
#include <engine/modules/ParticleSystem.h>
#include <ui/Glyph.h>

namespace ShyEngine
{
	class ParticleRenderer : Renderer<ParticleSystem, Glyph>
	{
		private:
		public:
			ParticleRenderer();
			~ParticleRenderer();
	};
}