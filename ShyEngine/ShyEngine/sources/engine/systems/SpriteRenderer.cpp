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

	void SpriteRenderer::createRenderBatches()
	{
		if (m_renderables.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph;

		int offset = 0;
		std::vector<Vertex> vertices;
		vertices.resize(m_renderables.size() * 6);

		// Putting the first sprite so that it can be used as a comparison in the next iterations
		m_renderBatches.emplace_back(offset, 6, m_renderablesPointers[0]->m_texture.id);
		vertices[currentVert++] = m_renderablesPointers[0]->m_topLeft;
		vertices[currentVert++] = m_renderablesPointers[0]->m_bottomLeft;
		vertices[currentVert++] = m_renderablesPointers[0]->m_bottomRight;
		vertices[currentVert++] = m_renderablesPointers[0]->m_bottomRight;
		vertices[currentVert++] = m_renderablesPointers[0]->m_topRight;
		vertices[currentVert++] = m_renderablesPointers[0]->m_topLeft;

		offset += 6;

		// Adding all the sprites
		for (currentGlyph = 1; currentGlyph < m_renderables.size(); currentGlyph++)
		{
			// Changing batch if the texture changes
			if (m_renderablesPointers[currentGlyph]->m_texture.id != m_renderablesPointers[currentGlyph - 1]->m_texture.id)
				m_renderBatches.emplace_back(offset, 6, m_renderablesPointers[currentGlyph]->m_texture.id);
			else
				m_renderBatches.back().nVertices += 6;

			vertices[currentVert++] = m_renderablesPointers[currentGlyph]->m_topLeft;
			vertices[currentVert++] = m_renderablesPointers[currentGlyph]->m_bottomLeft;
			vertices[currentVert++] = m_renderablesPointers[currentGlyph]->m_bottomRight;
			vertices[currentVert++] = m_renderablesPointers[currentGlyph]->m_bottomRight;
			vertices[currentVert++] = m_renderablesPointers[currentGlyph]->m_topRight;
			vertices[currentVert++] = m_renderablesPointers[currentGlyph]->m_topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteRenderer::sortSprites()
	{
		// Sort the sprites depending on the sort type
		switch (this->m_sortType)
		{
			case SpriteSortType::BACK_TO_FRONT:
			{
				std::stable_sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Sprite::compareBackToFront);
				break;
			}
			case SpriteSortType::FRONT_TO_BACK:
			{
				std::stable_sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Sprite::compareFrontToBack);
				break;
			}
			case SpriteSortType::TEXTURE:
			{
				std::stable_sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Sprite::compareTexture);
				break;
			}
			default:
				break;
		}
	}	
}