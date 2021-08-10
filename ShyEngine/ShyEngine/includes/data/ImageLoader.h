#pragma once

#include <data/Texture.h>
#include <string>
#include <data/picopng.h>
#include <input/EngineIO.h>
#include <util/Error.h>

namespace ShyEngine {
	class ImageLoader
	{
	public:
		static Texture loadPNG(std::string path);
	};
}