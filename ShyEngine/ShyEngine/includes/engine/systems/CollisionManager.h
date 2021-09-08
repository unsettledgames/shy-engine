#pragma once

#include <collisions/Collidable.h>
#include <data/SystemData.h>

#include <engine/Entity.h>
#include <engine/System.h>

#include <vector>

namespace ShyEngine
{
	class CollisionManager;

	class SpatialPartitioningCell
	{
		friend class CollisionManager;

		private:
			std::vector<Entity*> m_objects;
		public:
			SpatialPartitioningCell();
			~SpatialPartitioningCell() {}
	};

	class CollisionManager : public System
	{
		private:
			std::vector<SpatialPartitioningCell> m_cells;

			float m_gridCellSize = 20;
			glm::vec2 m_gridPosition = glm::vec2(0.0f, 0.0f);
			glm::vec2 m_gridSize = glm::vec2(100.0f, 100.0f);
			glm::vec2 m_nCells = glm::vec2(5, 5);

			int addToGrid(Entity* toAdd, int x, int y);

			void cellCollision(Collider2D* collider, int x, int y);

		public:
			CollisionManager(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize);
			CollisionManager() : System("CollisionManager") {}
			~CollisionManager() {}

			void updateModules(PhysicsData data);

			float getCellSize() { return m_gridCellSize; }
			void setCellSize(float size) { m_gridCellSize = size; }

			void addModule(Module* toAdd);
	};
}