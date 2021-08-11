#include <input/EventBus.h>

namespace ShyEngine
{
	_EventBus::_EventBus() {}

	// Use lambdas ffs
	void _EventBus::subscribe(std::string eventName, // Name of the event the callee is subscribing to
		void(*callback)(std::vector<void*>), // Pointer to the function used as a callback
		std::vector<void*> args)	// Pointer to the vector of arguments
	{
		// Find the vector corresponding to the event
		auto callbackVec = m_callbacks.find(eventName);
		// If it doesn't exist, I add it to the map
		if (callbackVec == m_callbacks.end())
			m_callbacks.emplace(std::make_pair(eventName, std::vector<void(*)(std::vector<void*>)>()));

		// Adding the callback to that event
		m_callbacks.emplace(std::make_pair(eventName, callback));
	}

	void _EventBus::fire(std::string eventName)
	{
		// Find the vector corresponding to the event
		auto callbackVec = m_callbacks.find(eventName);

		if (callbackVec != m_callbacks.end())
		{
			for (auto callback : callbackVec->second.first)
			{
				callback(callbackVec->second.second);
			}
		}
	}

	void _EventBus::unsubscribe(std::string eventName, void(*callback)(std::vector<void*>), std::vector<void*> args)
	{

	}
}