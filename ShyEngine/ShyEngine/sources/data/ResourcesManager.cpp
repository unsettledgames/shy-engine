#include <data/ResourcesManager.h>

namespace ShyEngine {
	TextureCache ResourcesManager::m_textureCache;

	Texture ResourcesManager::getTexture(std::string path)
	{
		return m_textureCache.getTexture(path);
	}
}