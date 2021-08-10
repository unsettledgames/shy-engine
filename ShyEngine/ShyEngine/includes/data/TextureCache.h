#pragma once

#include <map>
#include <string>
#include <data/Texture.h>
#include <data/ImageLoader.h>

namespace ShyEngine {
	class TextureCache
	{
	private:
		std::map<std::string, Texture> m_cache;

	public:
		TextureCache();

		Texture getTexture(std::string path);
	};
}