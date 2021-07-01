#include <Utility.h>

namespace ShyEngine {
	std::string Utility::getCwd()
	{
		std::string cwd(_getcwd(NULL, 0));
		return cwd;
	}

	void Utility::printOpenGLVersion()
	{
		std::printf("OPEN GL VERSION: %s\n", glGetString(GL_VERSION));
	}
}