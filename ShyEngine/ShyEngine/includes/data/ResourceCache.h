#pragma once

#include <map>
#include <functional>
#include <string>

namespace ShyEngine
{
	template <class T> 
	class ResourceCache
	{
		private:
			std::map<const std::string, T> m_resources;

			std::function<T(const std::string&)> m_loaderFunction;

		public:
			ResourceCache<T>(std::function<T(const std::string&)> loader)
			{
				m_loaderFunction = loader;
			}

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