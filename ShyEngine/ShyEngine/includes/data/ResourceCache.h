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
			std::map<std::string, T> m_resources;

			std::function<T(std::string)> m_loaderFunction;

		public:
			ResourceCache(std::function<T(std::string&)> loader);

			T get(std::string& path);
	};
}