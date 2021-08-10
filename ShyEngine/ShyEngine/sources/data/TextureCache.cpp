#include <data/TextureCache.h>

namespace ShyEngine {
	TextureCache::TextureCache()
	{

	}

	Texture TextureCache::getTexture(std::string path)
	{
		auto textureIter = m_cache.find(path);

		// Adding the texture if it isn't in the cache
		if (textureIter == m_cache.end())
		{
			Texture ret;
			ret = ImageLoader::loadPNG(path);
			m_cache.insert(make_pair(path, ret));

			return ret;
		}

		return textureIter->second;
	}
}