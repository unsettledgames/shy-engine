#include <data/ResourcesManager.h>

namespace ShyEngine {
	_ResourcesManager ResourcesManager;

	Texture _ResourcesManager::getTexture(std::string path)
	{
		return m_textureCache->get(path);
	}
}