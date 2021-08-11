#include <input/EventBus.h>

namespace ShyEngine
{
	_EventBus::_EventBus() {}

	void _EventBus::subscribe(std::string eventName, // Name of the event the callee is subscribing to
		std::function<void(std::vector<void*>)> callback) // Pointer to the function used as a callback
	{
		// Find the vector corresponding to the event
		auto callbackVec = m_callbacks.find(eventName);
		// If it doesn't exist, I add it to the map
		if (callbackVec == m_callbacks.end())
			m_callbacks.emplace(std::make_pair(eventName, std::vector<void(*)(std::vector<void*>)>()));

		// Adding the callback to that event
		m_callbacks.emplace(std::make_pair(eventName, callback));
	}

	void _EventBus::fire(std::string eventName, std::vector<void*> parameters)
	{
		// Find the vector corresponding to the event
		auto callbackVec = m_callbacks.find(eventName);

		// Call all its callbacks, pass the parameters
		if (callbackVec != m_callbacks.end())
		{
			for (auto callback : callbackVec->second)
			{
				callback(parameters);
			}
		}
	}

	void _EventBus::unsubscribe(std::string eventName, 
		std::function<void(std::vector<void*>)> callback)
	{
		// Find the vector for eventName and remove the callback
		auto callbackVec = m_callbacks.find(eventName);
		if (callbackVec != m_callbacks.end())
			remove(callbackVec->second.begin(), callbackVec->second.end(), callback);
	}
}