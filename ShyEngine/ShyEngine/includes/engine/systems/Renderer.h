#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <engine/System.h>
#include <data/RenderData.h>
#include <data/Glyph.h>
#include <data/Vertex.h>
#include <engine/modules/Sprite.h>

#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>

// OPTIMIZABLE: optimize the rendering process with less copies.
// OPTIMIZABLE: only update the render batches if the modules vector changed
// OPTIMIZABLE: https://discord.com/channels/506164002003484673/582608229629165578/882597437884235846

namespace ShyEngine
{
	template <class ModuleType, class RenderableType>
	class Renderer : public System
	{
		static_assert(std::is_base_of<Glyph, RenderableType>::value, "T must inherit from list");

		protected:
			// Modules to update
			std::vector<ModuleType> m_modulesToUpdate;
			// Pointers to the modules to update
			std::vector<ModuleType*> m_modulesPointers;

			// Used for sorting
			std::vector<RenderableType*> m_renderablesPointers;
			// Actual sprites
			std::vector<RenderableType> m_renderables;
			// List of batches
			std::vector<RenderBatch> m_renderBatches;

			// Vertex buffer object
			GLuint m_vbo = 0;
			// Vertex attribute object
			GLuint m_vao = 0;
			// Tells how to sort the sprites
			SpriteSortType m_sortType = SpriteSortType::TEXTURE;

		public:
			Renderer() : System() {};
			Renderer(const std::string& name) : System(name) {};
			~Renderer() {};

			/**
			*	Creates the vertex arrays, binds the attributes
			*/
			void createVertexArray()
			{
				// Generate the vertex attribute array and the vertex buffer object
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

			/**
			*	Marks the beginning of a rendering phase. Sets the sort type, initializes the process.
			*/
			void begin(SpriteSortType sortType = SpriteSortType::TEXTURE)
			{
				m_sortType = sortType;
				m_renderBatches.clear();

				m_renderables.clear();
				m_renderablesPointers.clear();

				m_modulesToUpdate.resize(m_modulesPointers.size());
				for (int i = 0; i < m_modulesPointers.size(); i++)
					m_modulesToUpdate[i] = (*(m_modulesPointers[i]));
			}

			/**
			*	Adds a sprite to the list of sprites to be drawn.
			*/
			void draw(RenderableType* toDraw)
			{
				m_renderables.emplace_back(*toDraw);
			}

			/**
			*	Marks the end of a rendering phase: sorts the sprites and creates the batches.
			*/
			void end()
			{
				// Update pointers for sorting
				m_renderablesPointers.resize(m_renderables.size());

				for (unsigned int i = 0; i < m_renderables.size(); i++)
					m_renderablesPointers[i] = &m_renderables[i];

				sortSprites();
				createRenderBatches();
			}

			/**
			*	Renders all the sprites
			*/
			void render()
			{
				glBindVertexArray(m_vao);

				for (unsigned int i = 0; i < m_renderBatches.size(); i++)
				{
					glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
					glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].nVertices);
				}

				glBindVertexArray(0);
			}

			void addModule(ModuleType* toAdd)
			{
				m_modulesPointers.push_back(toAdd);
			}

			/**
			*	Sorts the sprites depending on their texture
			*/
			void sortSprites()
			{
				// Sort the sprites depending on the sort type
				switch (this->m_sortType)
				{
				case SpriteSortType::BACK_TO_FRONT:
				{
					std::sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Glyph::compareBackToFront);
					break;
				}
				case SpriteSortType::FRONT_TO_BACK:
				{
					std::sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Glyph::compareFrontToBack);
					break;
				}
				case SpriteSortType::TEXTURE:
				{
					std::sort(m_renderablesPointers.begin(), m_renderablesPointers.end(), Glyph::compareTexture);
					break;
				}
				default:
					break;
				}
			}

			virtual void createRenderBatches()
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
	};
}