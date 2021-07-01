#include <string>
#include <direct.h>
#include <GL/glew.h>

class Utility
{
public:
	static std::string getCwd();

	static void printOpenGLVersion();
};
