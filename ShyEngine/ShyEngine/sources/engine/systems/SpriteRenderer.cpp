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

		for (auto _module : m_modulesToUpdate)
		{
			currSprite = dynamic_cast<Sprite*>(&_module);
			currSprite->updateVertices();
			// Only draw if the object is visible
			if (Collider2D::AABB(glm::vec4(currSprite->getPosition(), currSprite->getScale()), shaderData.cameraViewport))
				draw(currSprite);
		}

		end();

		// OPTIMIZABLE: use the correct shader lol
		m_modulesToUpdate[0].useShader();
		m_modulesToUpdate[0].getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);

		render();

		m_modulesToUpdate[0].unuseShader();
	}
}