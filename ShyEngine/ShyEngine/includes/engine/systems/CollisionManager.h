#pragma once

#include <engine/Entity.h>
#include <engine/System.h>
#include <engine/Module.h>

#include <collisions/Collidable.h>
#include <collisions/CollisionGrid.h>
#include <engine/modules/collisions/Collider2D.h>
#include <data/SystemData.h>

#include <vector>
#include <set>

namespace ShyEngine
{
	class CollisionManager;
	class Collider2D;
	class Collidable;

	class CollisionManager : public System
	{
		private:
			CollisionGrid* m_collisionGrid;
			std::vector<Collider2D> m_modules;
			std::set<Entity*> m_entities;

			void cellCollision(Collider2D* collider, int x, int y);
			void updateCellCoords(Collidable* entity);
			void moveEntity(Collidable* entity, glm::vec2 destCoords);
		public:
			CollisionManager(float cellSize, glm::vec2 gridPos, glm::vec2 gridSize);
			CollisionManager() : System("CollisionManager") {}
			~CollisionManager() {}

			void updateModules(PhysicsData data);
			void addModule(Collider2D* toAdd);
	};
}