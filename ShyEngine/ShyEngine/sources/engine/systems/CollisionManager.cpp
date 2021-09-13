#include <engine/systems/CollisionManager.h>

namespace ShyEngine
{
	SpatialPartitioningCell::SpatialPartitioningCell()
	{
		m_objects.reserve(50);
	}

	void CollisionManager::updateModules(PhysicsData data)
	{
		SpatialPartitioningCell currCell;
		std::vector<Entity*> currEntities;
		std::vector<Collider2D*> currColliders;
		std::vector<Module*> currModules;
		std::vector<Collidable*> currCollidables;

		int x, y;

		for (int i = 0; i < m_cells.size(); i++)
		{
			currCell = m_cells[i];
			currEntities = currCell.m_objects;

			x = i % (int)m_nCells.x;
			y = i / (int)m_nCells.x;

			// Take all the colliders of the current object
			for (auto currEntity : currEntities)
			{
				currColliders = currEntity->getModules<Collider2D>();

				for (auto currCollider : currColliders)
				{
					// OPTIMIZABLE: only check collisions if the boundaries of the object overlap more than 1 cell,
					// this doesn't apply for objects in the same cell
					
					// Top left
					cellCollision(currCollider, x - 1, y - 1);
					// Top
					cellCollision(currCollider, x, y - 1);
					// Left
					cellCollision(currCollider, x - 1, y);
					// Middle
					cellCollision(currCollider, x, y);
					// Bottom left
					cellCollision(currCollider, x - 1, y + 1);
				}
			}
		}
	}

	void CollisionManager::cellCollision(Collider2D* collider, int x, int y)
	{
		if (x < 0 || y < 0 || x >= m_nCells.x || y >= m_nCells.y)
			return;
		SpatialPartitioningCell cell = m_cells[y * m_nCells.y + x];
		std::vector<Collider2D*> currColliders;
		std::vector<Module*> currModules;
		std::vector<Collidable*> currCollidables;

		// Find list of colliders with which it collides
		for (auto currObject : cell.m_objects)
		{
			// Ignore collisions with colliders of the same object
			if (currObject->getId() != collider->getEntity()->getId())
			{
				currColliders = currObject->getModules<Collider2D>();

				// If it collides
				if (collider->checkCollisionOptimized(currColliders))
				{
					// Trigger the enter / stay functions for all the Collidable modules
					for (auto collidable : currObject->getModules<Collidable>())
						((Collidable*)collidable)->handleCollision(true);
				}
				else
				{
					// Trigger the enter / stay functions for all the Collidable modules
					for (auto collidable : currObject->getModules<Collidable>())
						((Collidable*)collidable)->handleCollision(false);
				}
			}
		}
	}

	void CollisionManager::addModule(Module* toAdd)
	{
		// Coordinates of the objects in the grid
		int xIndex;
		int yIndex;

		// Transform
		Transform* otherTransform = (Transform*)toAdd->getEntity()->getModule<Transform>();
		
		// Putting the object in the grid
		glm::vec2 otherPos = otherTransform->getPos();
		addToGrid(toAdd->getEntity(), std::round(otherPos.x), std::round(otherPos.y));

		m_modulesPointers.push_back(toAdd);
	}

	int CollisionManager::addToGrid(Entity* toAdd, int x, int y)
	{
		int index;

		x += m_gridSize.x / 2;
		y += m_gridSize.y / 2;
		index = y * m_gridSize.x + x;

		m_cells[index].m_objects.push_back(toAdd);

		return index;
	}

	CollisionManager::CollisionManager(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize) : System("CollisionManager")
	{
		m_gridCellSize = cellSize;
		m_gridPosition = gridPos;
		m_gridSize = gridSize;
	
		m_nCells = glm::vec2(std::ceil(m_gridSize.x / m_gridCellSize), std::ceil(m_gridSize.y / m_gridCellSize));
		m_cells.resize(m_nCells.x * m_nCells.y);
	}
}