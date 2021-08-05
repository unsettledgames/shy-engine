#pragma once

#include <ParticleBatch2D.h>
#include <vector>

namespace ShyEngine
{
	class ParticleEngine2D
	{
		private:
			std::vector<ParticleBatch2D*> m_particleBatches;

		public:
			ParticleEngine2D();
			~ParticleEngine2D();

			void init();
			
			void addParticleBatch(ParticleBatch2D* batch);

			void update();

			void draw(SpriteBatch* batch);
	};
}
