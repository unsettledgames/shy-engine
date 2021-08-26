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

		// REFACTOR: put this in the engine so they don't have to be repeated across Renderers
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);

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
		m_texts.push_back(toDraw);
		addGlyphs(toDraw->getGlyphs());
	}

	void TextRenderer::createRenderBatches()
	{
		if (m_renderables.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph = 0;

		int offset = 0;
		bool first = true;
		std::vector<Glyph> currGlyphs;
		std::vector<Vertex> vertices;

		currGlyphs = m_modulesToUpdate[0].getGlyphs();
		vertices.resize(currGlyphs.size() * 6);

		// Putting the first sprite so that it can be used as a comparison in the next iterations
		m_renderBatches.emplace_back(offset, 6, currGlyphs[0].m_texture.id);
		vertices[currentVert++] = currGlyphs[0].m_topLeft;
		vertices[currentVert++] = currGlyphs[0].m_bottomLeft;
		vertices[currentVert++] = currGlyphs[0].m_bottomRight;
		vertices[currentVert++] = currGlyphs[0].m_bottomRight;
		vertices[currentVert++] = currGlyphs[0].m_topRight;
		vertices[currentVert++] = currGlyphs[0].m_topLeft;

		offset += 6;

		for (Text t : m_modulesToUpdate)
		{
			for (Glyph s : t.getGlyphs())
			{
				if (!first)
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

				first = false;
			}
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
			m_glyphs.push_back(s);
			m_glyphPointers.push_back(&s);
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