#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace ShyEngine
{
	class _EventBus
	{
		private:
			// Used to save the callbacks. Keys are strings (event names) which are connected to 
			// a vector of callbacks. Those callbacks return void and have a single parameter, which is 
			// a vector of void*. Vectors of void* can be passed to fire(...) so that arguments can be
			// passed and used by the callbacks
			std::map<std::string, std::vector<std::function<void(std::vector<void*>)>>> m_callbacks;

		public:
			_EventBus();

			/** Adds a callback to the event called eventName
			* 
			*	@param eventName:	The name of the event that will trigger the callback
			*	@param callback:	The callback that will be called when the event is fired
			*/
			void subscribe(std::string eventName, std::function<void(std::vector<void*>)> callback);

			/** Fires the event eventName and calls all its connected callbacks
			* 
			*	@param eventName:	The name of the event to fire
			*	@param parameters:	The vector of parameters to pass to each callback
			*/
			void fire(std::string eventName, std::vector<void*> parameters);

			/** Removes callback from the list of functions called when the event eventName is fired
			* 
			*	@param eventName:	The name of the event to which the callback is connected
			*	@param callback:	The function to remove from the list of callbacks of eventName
			*/
			void unsubscribe(std::string eventName, std::function<void(std::vector<void*>)> callback);
	};

	_EventBus EventBus();
}