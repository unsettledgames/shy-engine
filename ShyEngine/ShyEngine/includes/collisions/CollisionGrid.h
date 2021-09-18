#pragma once

#include <vector>

#include <engine/Entity.h>

namespace ShyEngine
{
	class CollisionGrid;

	class SpatialPartitioningCell
	{
		friend class CollisionGrid;

		private:
			std::vector<Entity*> m_objects;
		public:
			SpatialPartitioningCell();
			~SpatialPartitioningCell() {}

			std::vector<Entity*> getObjects() { return m_objects; }
	};

	class CollisionGrid
	{
		private:
			std::vector<SpatialPartitioningCell> m_cells;

			float m_gridCellSize = 20;
			glm::vec2 m_gridPosition = glm::vec2(0.0f, 0.0f);
			glm::vec2 m_gridSize = glm::vec2(100.0f, 100.0f);
			glm::vec2 m_nCells = glm::vec2(5, 5);

		public:
			CollisionGrid(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize);
			CollisionGrid();

			SpatialPartitioningCell getCell(int index);
			SpatialPartitioningCell getCell(glm::vec2 pos);
			
			glm::vec2 getEntityCoords(Entity* e, int x, int y);
			// x and y are the integer approximation of toAdd's position
			glm::vec2 addToGrid(Entity* toAdd, int x, int y);
			// Here, instead, x and y are the actual grid coords
			void removeFromGrid(Entity* toRemove, int x, int y);

			float getCellSize() { return m_gridCellSize; }
			void setCellSize(float size) { m_gridCellSize = size; }

			glm::vec2 getGridPosition() { return m_gridPosition; }
			glm::vec2 getGridSize() { return m_gridSize; }
			glm::vec2 getNCells() { return m_nCells; }
	};
}