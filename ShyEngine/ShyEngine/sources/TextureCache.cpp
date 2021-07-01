#include <TextureCache.h>

TextureCache::TextureCache()
{

}

Texture TextureCache::getTexture(std::string path)
{
	auto textureIter = _cache.find(path);
	
	// Adding the texture if it isn't in the cache
	if (textureIter == _cache.end())
	{
		Texture ret;
		ret = ImageLoader::loadPNG(path);
		_cache.insert(make_pair(path, ret));

		return ret;
	}

	return textureIter->second;

}