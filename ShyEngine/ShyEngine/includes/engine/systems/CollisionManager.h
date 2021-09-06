#pragma once

#include <engine/System.h>

namespace ShyEngine
{
	class CollisionManager : public System
	{
		private:
		public:
			CollisionManager() : System("CollisionManager") {}
			~CollisionManager() {}

			void updateModules(PhysicsData data) {}
	};
}