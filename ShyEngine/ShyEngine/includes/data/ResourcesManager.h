#pragma once

#include <data/Texture.h>
#include <data/ImageLoader.h>
#include <data/ResourceCache.h>

namespace ShyEngine {

	static Texture loadTexture(std::string path)
	{
		Texture ret;
		ret = ImageLoader::loadPNG(path);

		return ret;
	}

	class _ResourcesManager
	{
		private:
			ResourceCache<Texture>* m_textureCache = new ResourceCache<Texture>(loadTexture);

		public:
			_ResourcesManager() {}
			Texture getTexture(std::string path);
		
	};

	extern _ResourcesManager ResourcesManager;
}