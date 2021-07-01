#pragma once

#include <Texture.h>
#include <string>
#include <picopng.h>
#include <EngineIO.h>
#include <Error.h>

namespace ShyEngine {
	class ImageLoader
	{
	public:
		static Texture loadPNG(std::string path);
	};
}