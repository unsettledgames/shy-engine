#include <SpriteBatch.h>

namespace ShyEngine
{

	SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0), m_sortType(GlyphSortType::TEXTURE)
	{

	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType)
	{
		this->m_sortType = sortType;
		this->m_renderBatches.clear();
		this->m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		// Update pointers for sorting
		m_glyphPointers.resize(m_glyphs.size());
		
		for (int i = 0; i < m_glyphs.size(); i++)
		{
			m_glyphPointers[i] = &m_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, float depth,
		const GLuint& texture, const ColorRGBA8& color)
	{
		this->m_glyphs.emplace_back(destRect, uvRect, depth, texture, color);
	}

	void SpriteBatch::render()
	{
		glBindVertexArray(m_vao);

		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].nVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
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

	void SpriteBatch::createRenderBatches()
	{
		if (m_glyphs.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph;

		int offset = 0;
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphs.size() * 6);

		m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
		vertices[currentVert++] = m_glyphPointers[0]->topLeft;
		vertices[currentVert++] = m_glyphPointers[0]->bottomLeft;
		vertices[currentVert++] = m_glyphPointers[0]->bottomRight;
		vertices[currentVert++] = m_glyphPointers[0]->bottomRight;
		vertices[currentVert++] = m_glyphPointers[0]->topRight;
		vertices[currentVert++] = m_glyphPointers[0]->topLeft;

		offset += 6;

		for (currentGlyph = 1; currentGlyph < m_glyphs.size(); currentGlyph++)
		{
			if (m_glyphPointers[currentGlyph]->texture != m_glyphPointers[currentGlyph - 1]->texture)
				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[currentGlyph]->texture);
			else
				m_renderBatches.back().nVertices += 6;
			vertices[currentVert++] = m_glyphPointers[currentGlyph]->topLeft;
			vertices[currentVert++] = m_glyphPointers[currentGlyph]->bottomLeft;
			vertices[currentVert++] = m_glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVert++] = m_glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVert++] = m_glyphPointers[currentGlyph]->topRight;
			vertices[currentVert++] = m_glyphPointers[currentGlyph]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (this->m_sortType)
		{
			case GlyphSortType::BACK_TO_FRONT:
			{
				std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
				break;
			}
			case GlyphSortType::FRONT_TO_BACK:
			{
				std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
				break;
			}
			case GlyphSortType::TEXTURE:
			{
				std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
				break;
			}
			default:
				break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return a->texture < b->texture;
	}
}