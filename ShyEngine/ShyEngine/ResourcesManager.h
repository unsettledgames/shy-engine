#pragma once

#include <TextureCache.h>

namespace ShyEngine {
	class ResourcesManager
	{
	private:
		static TextureCache m_textureCache;
	public:
		static Texture getTexture(std::string path);
	};
}