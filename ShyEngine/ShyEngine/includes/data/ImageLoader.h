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
		/*
			\brief	Loads a PNG file and creates a Texture with it
			\param path	The path of the file that should be used to create the texture

			\return	The texture based upon the specified file
		*/
		static Texture loadPNG(std::string path, GLint textureFiltering = GL_NEAREST,
			GLint mipmapFiltering = GL_NEAREST_MIPMAP_NEAREST);
	};
}