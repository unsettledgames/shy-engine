#pragma once

#include <map>
#include <functional>
#include <string>

namespace ShyEngine
{
	/*
		\brief	ResourceCache caches objects of type T for future use.

		When loading a resource (usually audio files or textures), the engine saves a copy in a map indexed by
		the file path of the resource in order to save time and memory.

		The user must provide a function that defines the way objects are loaded if they aren't already
		in the cache. At the moment, no replacement policy is applied and the cache can grow for as much as 
		the machine is able to handle.
	*/
	template <class T> 
	class ResourceCache
	{
		private:
			// The resources that have been loaded, indexed by their file path
			std::map<const std::string, T> m_resources;
			// The function used to load resources if they aren't already in the dictionary
			std::function<T(const std::string&)> m_loaderFunction;

		public:
			ResourceCache<T>(std::function<T(const std::string&)> loader)
			{
				m_loaderFunction = loader;
			}

			/*
				\brief	Returns the resource identified by the specified file path. If it's not already loaded,
					the loaderFunction is used to do so.

				\param path	The path of the file to resource
				
				\return The object identified by the file path passed as an argument
			*/
			T get(const std::string& path)
			{
				// Try to find the resource
				auto it = m_resources.find(path);
				T ret;

				// If it's not in the map, load it using the function
				if (it == m_resources.end())
				{
					ret = m_loaderFunction(path);
					m_resources.emplace(std::make_pair(path, m_loaderFunction(path)));
				}
				else
					ret = it->second;

				// Return the result
				return ret;
			}
	};
}