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
		std::vector<Sprite> glyphs = m_modulesToUpdate[0].getSprites();
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
			glyphs[0].getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);
			draw(dynamic_cast<Text*>(&_module));
		}

		end();
		render();

		glyphs[0].unuseShader();
	}

	void TextRenderer::draw(Text* toDraw)
	{
		m_texts.push_back(toDraw);
		addSprites(toDraw->getSprites());
	}

	void TextRenderer::createRenderBatches()
	{
		if (m_sprites.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph = 0;

		int offset = 0;
		bool first = true;
		std::vector<Sprite> currSprites;
		std::vector<Vertex> vertices;

		currSprites = m_modulesToUpdate[0].getSprites();
		vertices.resize(currSprites.size() * 6);

		// Putting the first sprite so that it can be used as a comparison in the next iterations
		m_renderBatches.emplace_back(offset, 6, currSprites[0].m_texture.id);
		vertices[currentVert++] = currSprites[0].m_topLeft;
		vertices[currentVert++] = currSprites[0].m_bottomLeft;
		vertices[currentVert++] = currSprites[0].m_bottomRight;
		vertices[currentVert++] = currSprites[0].m_bottomRight;
		vertices[currentVert++] = currSprites[0].m_topRight;
		vertices[currentVert++] = currSprites[0].m_topLeft;

		offset += 6;

		for (Text t : m_modulesToUpdate)
		{
			for (Sprite s : t.getSprites())
			{
				if (!first)
				{
					// Changing batch if the texture changes
					if (m_spritePointers[currentGlyph]->m_texture.id != m_spritePointers[currentGlyph - 1]->m_texture.id)
						m_renderBatches.emplace_back(offset, 6, m_spritePointers[currentGlyph]->m_texture.id);
					else
						m_renderBatches.back().nVertices += 6;

					vertices[currentVert++] = m_spritePointers[currentGlyph]->m_topLeft;
					vertices[currentVert++] = m_spritePointers[currentGlyph]->m_bottomLeft;
					vertices[currentVert++] = m_spritePointers[currentGlyph]->m_bottomRight;
					vertices[currentVert++] = m_spritePointers[currentGlyph]->m_bottomRight;
					vertices[currentVert++] = m_spritePointers[currentGlyph]->m_topRight;
					vertices[currentVert++] = m_spritePointers[currentGlyph]->m_topLeft;

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

	void TextRenderer::addSprites(std::vector<Sprite> toAdd)
	{
		for (Sprite s : toAdd)
		{
			m_sprites.push_back(s);
			m_spritePointers.push_back((Sprite*)s.m_reference);
		}
	}

	void TextRenderer::sortSprites()
	{
		// Sort the sprites depending on the sort type
		switch (this->m_sortType)
		{
		case SpriteSortType::BACK_TO_FRONT:
		{
			std::stable_sort(m_spritePointers.begin(), m_spritePointers.end(), Sprite::compareBackToFront);
			break;
		}
		case SpriteSortType::FRONT_TO_BACK:
		{
			std::stable_sort(m_spritePointers.begin(), m_spritePointers.end(), Sprite::compareFrontToBack);
			break;
		}
		case SpriteSortType::TEXTURE:
		{
			std::stable_sort(m_spritePointers.begin(), m_spritePointers.end(), Sprite::compareTexture);
			break;
		}
		default:
			break;
		}
	}
}