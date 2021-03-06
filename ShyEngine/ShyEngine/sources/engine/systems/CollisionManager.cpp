#include <engine/systems/CollisionManager.h>
#include <collisions/CollisionHandlers.h>

namespace ShyEngine
{
	SpatialPartitioningCell::SpatialPartitioningCell()
	{
		m_objects.reserve(25);
	}

	void CollisionManager::updateModules(PhysicsData data)
	{
		// Used to store the collidables of an object that is colliding
		std::vector<Collidable*> collidables;
		// The two colliders involved in a collision
		Collider2D* collider, * collider2;
		// The data resulting from a collision
		CollisionData collisionData;

		// Check every collider against the ones after them
		for (int i=0; i<m_modulesPointers.size(); i++)
		{
			for (int j=0; j< m_modulesPointers.size(); j++)
			{
				if (settings->collisions.collides(
					m_modulesPointers[i]->m_entity->getLayer(), m_modulesPointers[j]->m_entity->getLayer()))
				{
					collider = (Collider2D*)m_modulesPointers[i];
					collider2 = (Collider2D*)m_modulesPointers[j];

					collisionData = checkCollision(collider, collider2);
					collidables = collider->m_entity->m_collidables;

					// Trigger the enter / stay / exit functions for all the Collidable modules.
					// No, I can't avoid doing that if it's not colliding because Collidables need to know when
					// a collision ended. If they were not colliding the frame before the current one, they'll take
					// care of that and won't do anything
					for (int i = 0; i < collidables.size(); i++)
						collidables[i]->handleCollision(collisionData);
				}
				
			}
		}
	}

	// UNUSED
	void CollisionManager::cellCollision(Collider2D* collider, int x, int y)
	{
		/*glm::vec2 nCells = m_collisionGrid->getNCells();

		if (x < 0 || y < 0 || x >= nCells.x || y >= nCells.y)
			return;
		SpatialPartitioningCell* cell = m_collisionGrid->getCell(y * nCells.y + x);
		std::vector<Collider2D*> currColliders;
		
		// Find list of colliders with which it collides
		for (auto currObject : cell->getObjects())
		{
			// Ignore collisions with colliders of the same object
			// ISSUE: getModules is EXTREMELY slow
			currColliders = currObject->getModules<Collider2D>();
			// ISSUE: Collision checking is slow
			Collider2D* collidedCollider = collider->checkCollision(currColliders);
			// ISSUE: caching issues with ifs
			
			// If it collides
			if (collidedCollider != nullptr)
			{
				// Trigger the enter / stay functions for all the Collidable modules
				for (auto collidable : currObject->getModules<Collidable>())
					((Collidable*)collidable)->handleCollision(true, collidedCollider);
			}
			else
			{
				// Trigger the enter / stay functions for all the Collidable modules
				for (auto collidable : currObject->getModules<Collidable>())
				{
					Collidable* curr = (Collidable*)collidable;
					if (curr->m_currentCollider != nullptr)
						curr->handleCollision(false, nullptr);
				}
			}
		}*/
	}

	// UNUSED
	void CollisionManager::updateCellCoords(Collidable* coll)
	{
		glm::vec2 otherPos = coll->m_entity->getModule<Transform>()->getPos();

		moveEntity(coll, otherPos);
	}

	// UNUSED
	void CollisionManager::moveEntity(Collidable* entity, glm::vec2 destCoords)
	{
		glm::vec2 currCoords = entity->m_cellCoords;
		
		m_collisionGrid->removeFromGrid(entity->m_entity, currCoords.x, currCoords.y);
		m_collisionGrid->addToGrid(entity->m_entity, std::round(destCoords.x), std::round(destCoords.y));
	}

	void CollisionManager::addModule(Collider2D* toAdd)
	{
		// TODO: add compatibility and dependency checks
		m_entities.insert(toAdd->m_entity);
		m_modulesPointers.push_back(toAdd);
		m_modules.push_back(*toAdd);
	}

	CollisionManager::CollisionManager(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize) : System("CollisionManager")
	{
		m_collisionGrid = new CollisionGrid(cellSize, gridPos, gridSize);
	}
}