#include <string>
#include <direct.h>
#include <GL/glew.h>

namespace ShyEngine {
	class Utility
	{
	public:
		static std::string getCwd();

		static void printOpenGLVersion();
	};
}