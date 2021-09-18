#include <engine/systems/CollisionManager.h>

namespace ShyEngine
{
	SpatialPartitioningCell::SpatialPartitioningCell()
	{
		m_objects.reserve(50);
	}

	void CollisionManager::updateModules(PhysicsData data)
	{
		glm::vec2 nCells = m_collisionGrid->getNCells();
		SpatialPartitioningCell currCell;
		Collidable* currCollidable;
		std::vector<Entity*> currEntities;
		std::vector<Collider2D*> currColliders;
		std::vector<Module*> currModules;
		std::vector<Collidable*> currCollidables;

		int x, y, i;

		for (auto entity : m_entities)
		{
			currCollidable = entity->getModule<Collidable>();
			// For each entity, update its cell coords
			updateCellCoords(currCollidable);

			// Get other entities from the cell
			i = currCollidable->m_cellCoords.y * m_collisionGrid->getNCells().x + currCollidable->m_cellCoords.x;
			x = currCollidable->m_cellCoords.x;
			y = currCollidable->m_cellCoords.y;

			currColliders = entity->getModules<Collider2D>();
			/*
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
			}*/
		}
	}

	void CollisionManager::cellCollision(Collider2D* collider, int x, int y)
	{
		glm::vec2 nCells = m_collisionGrid->getNCells();

		if (x < 0 || y < 0 || x >= nCells.x || y >= nCells.y)
			return;
		SpatialPartitioningCell cell = m_collisionGrid->getCell(y * nCells.y + x);
		std::vector<Collider2D*> currColliders;
		std::vector<Module*> currModules;
		std::vector<Collidable*> currCollidables;

		// Find list of colliders with which it collides
		for (auto currObject : cell.getObjects())
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

	void CollisionManager::updateCellCoords(Collidable* coll)
	{
		glm::vec2 otherPos = coll->getEntity()->getModule<Transform>()->getPos();

		moveEntity(coll, otherPos);
	}

	// OPTIMIZABLE: this takes a lot of resources for some reason
	void CollisionManager::moveEntity(Collidable* entity, glm::vec2 destCoords)
	{
		glm::vec2 currCoords = entity->m_cellCoords;
		
		m_collisionGrid->removeFromGrid(entity->getEntity(), currCoords.x, currCoords.y);
		m_collisionGrid->addToGrid(entity->getEntity(), std::round(destCoords.x), std::round(destCoords.y));
	}

	void CollisionManager::addModule(Collidable* toAdd)
	{
		// Coordinates of the objects in the grid
		int xIndex;
		int yIndex;

		// Transform
		Transform* otherTransform = (Transform*)toAdd->getEntity()->getTransform();
		
		// Putting the object in the grid
		glm::vec2 otherPos = otherTransform->getPos();
		glm::vec2 cellCoords = m_collisionGrid->addToGrid(toAdd->getEntity(), std::round(otherPos.x), std::round(otherPos.y));

		toAdd->m_collisionGrid = m_collisionGrid;
		toAdd->m_cellCoords = cellCoords;

		// it's useless to use modulesPointers, only fill m_entities
		m_entities.insert(toAdd->getEntity());
		m_modulesPointers.push_back(toAdd);
	}

	CollisionManager::CollisionManager(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize) : System("CollisionManager")
	{
		m_collisionGrid = new CollisionGrid(cellSize, gridPos, gridSize);
	}
}