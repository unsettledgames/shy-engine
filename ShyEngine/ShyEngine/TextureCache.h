#pragma once

#include <map>
#include <string>
#include <Texture.h>
#include <ImageLoader.h>

namespace ShyEngine {
	class TextureCache
	{
	private:
		std::map<std::string, Texture> _cache;

	public:
		TextureCache();

		Texture getTexture(std::string path);
	};
}