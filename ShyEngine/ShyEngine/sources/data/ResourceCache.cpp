#include <data/ResourceCache.h>

namespace ShyEngine
{
	template <class T>
	ResourceCache<T>::ResourceCache(std::function<T(std::string&)> loader) 
	{
		m_loaderFunction = loader;
	}

	template <class T>
	T ResourceCache<T>::get(std::string& path)
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
}