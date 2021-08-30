#include <engine/systems/ParticleRenderer.h>

namespace ShyEngine
{
	void ParticleRenderer::updateModules()
	{
		begin();

		for (int i = 0; i < m_modulesToUpdate.size(); i++)
		{
			draw(m_modulesToUpdate[i].getParticles());
		}

		end();
		render();
	}

	void ParticleRenderer::draw(std::vector<Particle> particles)
	{
		m_renderables.insert(m_renderables.begin(), particles.begin(), particles.end());
	}
}