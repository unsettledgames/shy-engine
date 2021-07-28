#include <SpriteBatch.h>

namespace ShyEngine
{

	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0), _sortType(GlyphSortType::TEXTURE)
	{

	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType)
	{
		this->_sortType = sortType;
		this->_renderBatches.clear();
		this->_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		// Update pointers for sorting
		_glyphPointers.resize(_glyphs.size());
		
		for (int i = 0; i < _glyphs.size(); i++)
		{
			_glyphPointers[i] = &_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, float depth,
		const GLuint& texture, const ColorRGBA8& color)
	{
		this->_glyphs.emplace_back(destRect, uvRect, depth, texture, color);
	}

	void SpriteBatch::render()
	{
		glBindVertexArray(_vao);

		for (unsigned int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].nVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (_vao == 0)
			glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		if (_vbo == 0)
			glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

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
		if (_glyphs.empty())
			return;

		unsigned int currentVert = 0;
		unsigned int currentGlyph;

		int offset = 0;
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

		_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
		vertices[currentVert++] = _glyphPointers[0]->topLeft;
		vertices[currentVert++] = _glyphPointers[0]->bottomLeft;
		vertices[currentVert++] = _glyphPointers[0]->bottomRight;
		vertices[currentVert++] = _glyphPointers[0]->bottomRight;
		vertices[currentVert++] = _glyphPointers[0]->topRight;
		vertices[currentVert++] = _glyphPointers[0]->topLeft;

		offset += 6;

		for (currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++)
		{
			if (_glyphPointers[currentGlyph]->texture != _glyphPointers[currentGlyph - 1]->texture)
				_renderBatches.emplace_back(offset, 6, _glyphPointers[currentGlyph]->texture);
			else
				_renderBatches.back().nVertices += 6;
			vertices[currentVert++] = _glyphPointers[currentGlyph]->topLeft;
			vertices[currentVert++] = _glyphPointers[currentGlyph]->bottomLeft;
			vertices[currentVert++] = _glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVert++] = _glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVert++] = _glyphPointers[currentGlyph]->topRight;
			vertices[currentVert++] = _glyphPointers[currentGlyph]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (this->_sortType)
		{
			case GlyphSortType::BACK_TO_FRONT:
			{
				std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
				break;
			}
			case GlyphSortType::FRONT_TO_BACK:
			{
				std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
				break;
			}
			case GlyphSortType::TEXTURE:
			{
				std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
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