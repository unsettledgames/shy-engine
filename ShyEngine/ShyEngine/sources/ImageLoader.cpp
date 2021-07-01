#include <ImageLoader.h>

Texture ImageLoader::loadPNG(std::string path)
{
	// OPTIMIZABLE: return a pointer, not the texture, should be deallocated though
	Texture ret = {};

	std::vector<unsigned char> outBuffer;
	std::vector<unsigned char> inData;
	unsigned long width, height;

	if (!EngineIO::readFileToBuffer(path, inData))
		Error::fatal("Failed to read from file " + path);

	// Error handling
	int err = decodePNG(outBuffer, width, height, &(inData[0]), inData.size());
	if (err != 0)
		Error::fatal("Failed to decode texture (error " + std::to_string(err) + ")");

	glGenTextures(1, &(ret.id));
	glBindTexture(GL_TEXTURE_2D, ret.id);
	// EXPANDABLE: second parameter is mipmapping, third is colour mode, border?
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)&(outBuffer[0]));
	// EXPANDABLE: texture wrapping (clamp / repeat etc)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// EXPANDABLE: point / bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	ret.width = width;
	ret.height = height;

	return ret;
}