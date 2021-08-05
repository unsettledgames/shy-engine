#include <ParticleEngine2D.h>

namespace ShyEngine
{
	ParticleEngine2D::ParticleEngine2D() {}

	ParticleEngine2D::~ParticleEngine2D() 
	{
		for (auto pb : m_particleBatches)
			delete pb;
	}

	void ParticleEngine2D::init()
	{

	}

	void ParticleEngine2D::addParticleBatch(ParticleBatch2D* batch)
	{
		m_particleBatches.push_back(batch);
	}

	void ParticleEngine2D::update()
	{
		for (auto pb : m_particleBatches)
			pb->update();
	}

	void ParticleEngine2D::draw(SpriteBatch* batch)
	{
		// OPTIMIZABLE: force particle system to use the same texture so you can put begin, end and render
		// outside of the loop
		for (auto particleBatch : m_particleBatches)
		{
			batch->begin();

			particleBatch->draw(batch);

			batch->end();
			batch->render();
		}
		
	}
}
