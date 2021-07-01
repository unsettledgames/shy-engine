#pragma once

#include <TextureCache.h>

namespace ShyEngine {
	class ResourcesManager
	{
	private:
		static TextureCache _textureCache;
	public:
		static Texture getTexture(std::string path);
	};
}