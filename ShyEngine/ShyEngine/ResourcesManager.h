#pragma once

#include <TextureCache.h>

class ResourcesManager
{
private:
	static TextureCache _textureCache;
public:	
	static Texture getTexture(std::string path);
};