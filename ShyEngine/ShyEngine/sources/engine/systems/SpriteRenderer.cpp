#include <engine/systems/SpriteRenderer.h>

namespace ShyEngine
{
	SpriteRenderer::SpriteRenderer() : Renderer("SpriteRenderer")
	{
		createVertexArray();
	}

	void SpriteRenderer::updateModules(ShaderData shaderData)
	{
		Sprite* currSprite;

		// OPTIMIZABLE: sort sprites by shaders? Organize batches by texture + shader
		// Rendering process
		begin();

		// OPTIMIZABLE: use the correct shader lol
		m_modulesToUpdate[0].useShader();

		for (auto _module : m_modulesToUpdate)
		{
			m_modulesToUpdate[0].getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);
			currSprite = dynamic_cast<Sprite*>(&_module);
			draw(currSprite);
		}

		end();
		render();

		m_modulesToUpdate[0].unuseShader();
	}
}