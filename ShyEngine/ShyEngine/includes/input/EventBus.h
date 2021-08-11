#pragma once

#include <string>
#include <map>
#include <vector>

namespace ShyEngine
{
	class _EventBus
	{
		private:
			std::map<std::string, std::pair<std::vector<void (*)(std::vector<void*>)>, std::vector<void*>>> m_callbacks;

		public:
			_EventBus();

			void subscribe(std::string eventName, void(*callback)(std::vector<void*>), std::vector<void*> args);

			void fire(std::string eventName);

			void unsubscribe(std::string eventName, void(*callback)(std::vector<void*>), std::vector<void*> args);
	};

	_EventBus EventBus();
}