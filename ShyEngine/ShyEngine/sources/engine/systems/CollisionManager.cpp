#include <engine/systems/CollisionManager.h>
#include <engine/modules/collisions/CircleCollider2D.h>

namespace ShyEngine
{
	SpatialPartitioningCell::SpatialPartitioningCell()
	{
		m_objects.reserve(25);
	}

	void CollisionManager::updateModules(PhysicsData data)
	{
		std::vector<Collidable*> collidables;
		Collider2D* collider, * collider2;
		int i = 0;

		// Ganzo, questo è esponenziale probabilmente (o almeno il calo di framerate è logaritmico)
		for (int i=0; i<m_modulesPointers.size(); i++)
		{
			for (int j=i+1; j< m_modulesPointers.size(); j++)
			{
				collider = (Collider2D*)m_modulesPointers[i];
				collider2 = (Collider2D*)m_modulesPointers[j];

				// If it collides
				if (collider->checkCollision(collider2))
				{
					collidables = collider->getEntity()->getModules<Collidable>();
					// Trigger the enter / stay functions for all the Collidable modules
					for (int i = 0; i < collidables.size(); i++)
					{
						collidables[i]->handleCollision(true, collider2);
						i++;
					}
				}
				else
				{
					collidables = collider->getEntity()->getModules<Collidable>();
					// Trigger the enter / stay functions for all the Collidable modules
					for (int i = 0; i < collidables.size(); i++)
					{
						if (collidables[i]->m_currentCollider != nullptr)
							collidables[i]->handleCollision(false, nullptr);
						i++;
					}
				}
			}

			std::printf("Iterations: %d\n", i);
		}
		/*
		glm::vec2 nCells = m_collisionGrid->getNCells();
		SpatialPartitioningCell currCell;
		Collidable* currCollidable;
		std::vector<Collider2D*> currColliders;
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
			
			for (auto currCollider : currColliders)
			{
				// OPTIMIZABLE: only check collisions if the boundaries of the object overlap more than 1 cell,
				// this doesn't apply for objects in the same cell
				// Top left
				cellCollision(currCollider, x - 1, y - 1);
				/*
				// Top
				cellCollision(currCollider, x, y - 1);
				// Left
				cellCollision(currCollider, x - 1, y);
				// Middle
				cellCollision(currCollider, x, y);
				// Bottom left
				cellCollision(currCollider, x - 1, y + 1);
				
			}
		}*/
	}

	// ISSUE: this is ExTREMELY slow
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

	void CollisionManager::addModule(Collider2D* toAdd)
	{
		m_entities.insert(toAdd->getEntity());
		m_modulesPointers.push_back(toAdd);
		m_modules.push_back(*toAdd);
		/*
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
		*/
	}

	CollisionManager::CollisionManager(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize) : System("CollisionManager")
	{
		m_collisionGrid = new CollisionGrid(cellSize, gridPos, gridSize);
	}
}