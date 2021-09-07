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
		std::vector<Collidable*> currCollidables;
		int x, y;

		for (int i = 0; i < m_cells.size(); i++)
		{
			currCell = m_cells[i];
			currCollidables = currCell.m_objects;

			x = i % (int)m_nCells.x;
			y = i / (int)m_nCells.x;

			// General process, should probably delete a few loops

			// Take all the colliders of the current object
			// For each collider
				// Find list of colliders with which it collides in the following cells:
					// Top left
					// Top
					// Left
					// Middle
					// Bottom left
				// For each of those colliders
					// Get all the modules of the entity to which that collider is attached
					// For each module
						// If it's Collidable
							// Call the collision functions
				
		}
	}

	void CollisionManager::addModule(Module* toAdd)
	{
		// Coordinates of the objects in the grid
		int xIndex;
		int yIndex;

		// Transform
		Transform* otherTransform = (Transform*)toAdd->getEntity()->getModule("Transform");
		// Adding only a single collidable, as the other ones will be triggered when colliding
		Collidable* otherCollidable = (Collidable*)toAdd->getEntity()->getModule("Collidable");
		
		// Putting the object in the grid
		glm::vec2 otherPos = otherTransform->getPos();
		addToGrid(otherCollidable, std::round(otherPos.x), std::round(otherPos.y));

		m_modulesPointers.push_back(toAdd);
	}

	int CollisionManager::addToGrid(Collidable* toAdd, int x, int y)
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