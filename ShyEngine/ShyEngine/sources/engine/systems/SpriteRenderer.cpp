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

		// IMPROVEMENT: implement depth sorting
		begin();

		for (auto _module : m_modulesPointers)
		{
			// Update the vertices of the sprite before drawing it: this is so that changes made by the collision
			// or physics system are taken in account
			currSprite = dynamic_cast<Sprite*>(_module);
			currSprite->updateVertices();
			// Only draw if the object is visible
			if (Collider2D::AABB(glm::vec4(currSprite->getPosition(), currSprite->getScale()), shaderData.cameraViewport))
				draw(currSprite);
		}

		end();

		// IMPROVEMENT: use the correct shader
		m_modulesPointers[0]->useShader();
		m_modulesPointers[0]->getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);

		render();

		m_modulesPointers[0]->unuseShader();
	}
}