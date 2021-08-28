#pragma once

#include <engine/Module.h>
#include <data/ColorRGBA8.h>

namespace ShyEngine
{
	class ParticleSystem : Module
	{
		private:
			ColorRGBA8 m_color = ColorRGBA8(255, 255, 255, 255);
			float m_lifetime = 0.0f;
		public:
			ParticleSystem();
			~ParticleSystem();
	};
}