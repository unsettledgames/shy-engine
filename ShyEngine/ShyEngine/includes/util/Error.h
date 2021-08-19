#pragma once

#include <string>

namespace ShyEngine {
	class Error
	{
	private:
	public:
		static void fatal(std::string error);

		static void runtime(std::string error);
	};
}