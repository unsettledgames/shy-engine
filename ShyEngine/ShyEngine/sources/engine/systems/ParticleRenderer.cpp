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

			for (int i = 0; i < m_modulesPointers.size(); i++)
			{
				m_modulesPointers[i]->update(shaderData.deltaTime);
				// The bug is probably at particle level
				draw(m_modulesToUpdate[i].getParticles());
			}

			end();

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

			render();

			if (useShader)
				particleShader.unuseShader();
		}
	}

	void ParticleRenderer::draw(std::vector<Particle> particles)
	{
		for (Particle p : particles)
			if (p.getLifetime() > 0)
				m_renderables.emplace_back(p);
	}
}