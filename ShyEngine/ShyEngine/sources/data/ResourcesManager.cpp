#include <data/ResourcesManager.h>

namespace ShyEngine {
	_ResourcesManager ResourcesManager;

	Texture _ResourcesManager::getTexture(const std::string& path)
	{
		return m_textureCache->get(path);
	}

	Music _ResourcesManager::getMusic(const std::string& path)
	{
		return m_musicCache->get(path);
	}

	SoundEffect _ResourcesManager::getSoundEffect(const std::string& path)
	{
		return m_sfxCache->get(path);
	}
}