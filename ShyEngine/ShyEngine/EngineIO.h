#pragma once

#include <vector>
#include <iostream>
#include <fstream>

namespace ShyEngine {
	class EngineIO
	{
	private:
	public:
		static bool readFileToBuffer(std::string& path, std::vector<unsigned char>& buffer);
	};
}