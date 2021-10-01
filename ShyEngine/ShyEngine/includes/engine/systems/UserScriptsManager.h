#pragma once

#include <engine/System.h>

namespace ShyEngine
{
	class UserScriptManager : public System
	{
		private:
		public:
			void init();
			void updateModules();
	};
}