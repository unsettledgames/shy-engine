#include <engine/systems/SpriteRenderer.h>

namespace ShyEngine
{
	SpriteRenderer::SpriteRenderer() : System("SpriteRenderer")
	{
		createVertexArray();
	}

	void SpriteRenderer::begin(SpriteSortType sortType)
	{
		m_sortType = sortType;
		m_renderBatches.clear();
		m_sprites.clear();
	}

	void SpriteRenderer::draw(Sprite* toDraw)
	{
		// OPTIMIZABLE: save the transform as well?
		m_spritePointers.emplace_back(toDraw);
	}

	void SpriteRenderer::end()
	{
		// Update pointers for sorting
		m_spritePointers.resize(m_sprites.size());

		for (int i = 0; i < m_sprites.size(); i++)
			m_spritePointers[i] = &m_sprites[i];

		sortSprites();
		createRenderBatches();
	}

	void SpriteRenderer::render()
	{
		glBindVertexArray(m_vao);

		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].nVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteRenderer::createVertexArray()
	{
		if (m_vao == 0)
			glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		if (m_vbo == 0)
			glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// Enabling arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Bind position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// Bind color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// Bind UVs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteRenderer::createRenderBatches()
	{
		if (m_sprites.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph;

		int offset = 0;
		std::vector<Vertex> vertices;
		vertices.resize(m_sprites.size() * 6);

		m_renderBatches.emplace_back(offset, 6, m_spritePointers[0]->m_texture.id);
		vertices[currentVert++] = m_spritePointers[0]->m_topLeft;
		vertices[currentVert++] = m_spritePointers[0]->m_bottomLeft;
		vertices[currentVert++] = m_spritePointers[0]->m_bottomRight;
		vertices[currentVert++] = m_spritePointers[0]->m_bottomRight;
		vertices[currentVert++] = m_spritePointers[0]->m_topRight;
		vertices[currentVert++] = m_spritePointers[0]->m_topLeft;

		offset += 6;

		for (currentGlyph = 1; currentGlyph < m_sprites.size(); currentGlyph++)
		{
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

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteRenderer::updateModules()
	{
		begin();

		for (auto _module : m_modulesToUpdate)
		{
			draw(dynamic_cast<Sprite*>(&_module));
		}

		end();
		render();
	}

	void SpriteRenderer::sortSprites()
	{
		switch (this->m_sortType)
		{
		case SpriteSortType::BACK_TO_FRONT:
		{
			std::stable_sort(m_spritePointers.begin(), m_spritePointers.end(), compareBackToFront);
			break;
		}
		case SpriteSortType::FRONT_TO_BACK:
		{
			std::stable_sort(m_spritePointers.begin(), m_spritePointers.end(), compareFrontToBack);
			break;
		}
		case SpriteSortType::TEXTURE:
		{
			std::stable_sort(m_spritePointers.begin(), m_spritePointers.end(), compareTexture);
			break;
		}
		default:
			break;
		}
	}

	bool SpriteRenderer::compareFrontToBack(Sprite* a, Sprite* b)
	{
		return a->m_depth < b->m_depth;
	}

	bool SpriteRenderer::compareBackToFront(Sprite* a, Sprite* b)
	{
		return a->m_depth > b->m_depth;
	}

	bool SpriteRenderer::compareTexture(Sprite* a, Sprite* b)
	{
		return a->m_texture.id < b->m_texture.id;
	}
}