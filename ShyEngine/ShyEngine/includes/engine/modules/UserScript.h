#pragma once

#include <collisions/Collidable.h>
#include <util/Classes.h>

namespace ShyEngine
{
	class UserScript : public Collidable
	{
		CLASS_DECLARATION(UserScript);

		private:

		public:
			UserScript() {};

			virtual void init() {}
			virtual void update() {}
			// ??? 
			virtual void lateUpdate() {}

			/*
			virtual void onEnable();
			virtual void onDisable();
			*/
	};
}