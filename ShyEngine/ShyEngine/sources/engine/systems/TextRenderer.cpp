#include <engine/systems/TextRenderer.h>

namespace ShyEngine
{
	TextRenderer::TextRenderer() : Renderer("SpriteRenderer")
	{
		createVertexArray();
	}

	void TextRenderer::updateModules(ShaderData shaderData)
	{
		Text* currText;
		std::vector<Glyph> glyphs = m_modulesToUpdate[0].getGlyphs();
		// OPTIMIZABLE: sort sprites by shaders? Organize batches by texture + shader
		// Rendering process
		begin();

		// OPTIMIZABLE: use the correct shader lol
		glyphs[0].useShader();

		for (auto _module : m_modulesToUpdate)
		{
			glyphs[0].getShader().setOrthoProjection("orthoProj", shaderData.cameraMatrix);
			draw(dynamic_cast<Text*>(&_module));
		}

		end();
		render();

		glyphs[0].unuseShader();
	}

	void TextRenderer::draw(Text* toDraw)
	{
		addGlyphs(toDraw->getGlyphs());
	}

	void TextRenderer::createRenderBatches()
	{
		if (m_renderables.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph = 0;

		int offset = 0;
		std::vector<Vertex> vertices;
		Glyph currGlyph = m_renderables[0];

		vertices.resize(m_renderables.size() * 6);

		// Putting the first sprite so that it can be used as a comparison in the next iterations
		m_renderBatches.emplace_back(offset, 6, currGlyph.m_texture.id);
		vertices[currentVert++] = currGlyph.m_topLeft;
		vertices[currentVert++] = currGlyph.m_bottomLeft;
		vertices[currentVert++] = currGlyph.m_bottomRight;
		vertices[currentVert++] = currGlyph.m_bottomRight;
		vertices[currentVert++] = currGlyph.m_topRight;
		vertices[currentVert++] = currGlyph.m_topLeft;

		offset += 6;

		for (int i = 1; i < m_renderables.size(); i++)
		{
			// Changing batch if the texture changes
			if (m_renderablesPointers[i]->m_texture.id != m_renderablesPointers[i - 1]->m_texture.id)
				m_renderBatches.emplace_back(offset, 6, m_renderablesPointers[i]->m_texture.id);
			else
				m_renderBatches.back().nVertices += 6;

			vertices[currentVert++] = m_renderablesPointers[i]->m_topLeft;
			vertices[currentVert++] = m_renderablesPointers[i]->m_bottomLeft;
			vertices[currentVert++] = m_renderablesPointers[i]->m_bottomRight;
			vertices[currentVert++] = m_renderablesPointers[i]->m_bottomRight;
			vertices[currentVert++] = m_renderablesPointers[i]->m_topRight;
			vertices[currentVert++] = m_renderablesPointers[i]->m_topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void TextRenderer::addGlyphs(std::vector<Glyph> toAdd)
	{
		for (Glyph s : toAdd)
		{
			m_renderables.push_back(s);
			m_renderablesPointers.push_back(&s);
		}
	}

	void TextRenderer::sortSprites()
	{
		// Sort the sprites depending on the sort type
		switch (this->m_sortType)
		{
		case SpriteSortType::BACK_TO_FRONT:
		{
			std::stable_sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Glyph::compareBackToFront);
			break;
		}
		case SpriteSortType::FRONT_TO_BACK:
		{
			std::stable_sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Glyph::compareFrontToBack);
			break;
		}
		case SpriteSortType::TEXTURE:
		{
			std::stable_sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Glyph::compareTexture);
			break;
		}
		default:
			break;
		}
	}
}