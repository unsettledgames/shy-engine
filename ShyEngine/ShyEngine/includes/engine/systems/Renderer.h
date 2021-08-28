#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <engine/System.h>
#include <data/RenderData.h>
#include <data/Vertex.h>
#include <engine/modules/Sprite.h>

#include <vector>
#include <string>
#include <algorithm>
// REFACTOR: change spritePointers and sprites to glyphPointers and glyphs

namespace ShyEngine
{
	template <class ModuleType, class RenderableType>
	class Renderer : public System
	{
		protected:
			// Sprites to render
			std::vector<ModuleType> m_modulesToUpdate;

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
			}

			/**
			*	Adds a sprite to the list of sprites to be drawn.
			*/
			void draw(RenderableType* toDraw)
			{
				// OPTIMIZABLE: save the transform as well?
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

			void addModule(ModuleType toAdd)
			{
				m_modulesToUpdate.push_back(toAdd);
			}

			virtual void sortSprites() = 0;
			virtual void createRenderBatches() = 0;
	};
}