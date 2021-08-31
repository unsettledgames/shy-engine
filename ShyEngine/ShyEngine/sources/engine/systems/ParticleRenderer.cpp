#include <engine/systems/ParticleRenderer.h>

namespace ShyEngine
{
	void ParticleRenderer::updateModules(ShaderData& shaderData)
	{
		if (m_modulesToUpdate.size() > 0)
		{
			std::vector<Particle> firstParticles = m_modulesToUpdate[0].getParticles();
			Particle firstParticle;

			begin();

			if (firstParticles.size() > 0)
			{
				firstParticle = m_modulesToUpdate[0].getParticles()[0];
				firstParticle.useShader();
				firstParticle.getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);
			}

			for (int i = 0; i < m_modulesToUpdate.size(); i++)
			{
				m_modulesToUpdate[i].update(shaderData.deltaTime);
				draw(m_modulesToUpdate[i].getParticles());
			}

			end();
			render();

			if (firstParticles.size() > 0)
				firstParticle.unuseShader();
		}
	}

	void ParticleRenderer::draw(std::vector<Particle> particles)
	{
		m_renderables.insert(m_renderables.begin(), particles.begin(), particles.end());
	}
}