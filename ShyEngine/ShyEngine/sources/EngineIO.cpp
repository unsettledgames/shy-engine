#include <EngineIO.h>

namespace ShyEngine {
	bool EngineIO::readFileToBuffer(std::string& path, std::vector<unsigned char>& buffer)
	{
		int fileSize;
		std::ifstream file(path, std::ios::binary);

		if (file.fail())
		{
			perror(("Opening file " + path).c_str());
			return false;
		}

		// Getting file size
		file.seekg(0, std::ios::end);
		fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		// Remove header bytes
		fileSize -= file.tellg();

		// Read file
		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}