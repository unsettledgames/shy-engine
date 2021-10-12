#pragma once

#include <engine/System.h>

namespace ShyEngine
{
	class UserScriptsManager : public System
	{
		private:
		public:
			UserScriptsManager() : System("UserScriptsManager") {}

			void init();
			void updateModules();
	};
}