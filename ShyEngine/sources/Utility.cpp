#include <Utility.h>

std::string Utility::getCwd()
{
	std::string cwd(_getcwd(NULL, 0));
	return cwd;
}