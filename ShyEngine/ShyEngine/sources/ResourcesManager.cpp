#include <ResourcesManager.h>

TextureCache ResourcesManager::_textureCache;

Texture ResourcesManager::getTexture(std::string path)
{
	return _textureCache.getTexture(path);
}