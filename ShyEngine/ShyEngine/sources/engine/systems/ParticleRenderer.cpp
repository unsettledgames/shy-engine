#include <engine/systems/ParticleRenderer.h>

namespace ShyEngine
{
	ParticleRenderer::ParticleRenderer() : Renderer<ParticleSystem, Particle>("ParticleRenderer")
	{
		createVertexArray();
	}

	void ParticleRenderer::updateModules(ShaderData& shaderData)
	{
		if (m_modulesPointers.size() > 0)
		{
			bool useShader = false;

			begin();
			m_renderables.clear();

			std::vector<Particle> firstParticles = m_modulesToUpdate[0].getParticles();
			Particle particleShader;

			for (int i = 0; i < firstParticles.size(); i++)
			{
				if (firstParticles[i].getLifetime() > 0)
				{
					particleShader = firstParticles[i];
					useShader = true;
					break;
				}
			}

			if (useShader)
			{
				particleShader.useShader();
				particleShader.getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);
			}

			for (int i = 0; i < m_modulesPointers.size(); i++)
			{
				m_modulesPointers[i]->update(shaderData.deltaTime);
				draw(m_modulesToUpdate[i].getParticles());
			}

			end();
			render();

			if (useShader)
				particleShader.unuseShader();
		}
	}

	void ParticleRenderer::draw(std::vector<Particle> particles)
	{
		m_renderables.insert(m_renderables.begin(), particles.begin(), particles.end());
	}
}