#include <util/Error.h>
#include <SDL/SDL.h>
#include <iostream>
#include <cstdlib>

namespace ShyEngine {
	void Error::fatal(std::string error)
	{
		std::cout << "FATAL: " << error << std::endl;

		if (error.find("SDL") != std::string::npos || error.find("Glew") != std::string::npos)
			std::cout << "The error seems to be associated with SDL or glew. Printing error: " << SDL_GetError() << std::endl;
		perror("Printing perror");
		SDL_Quit();
		exit(-1);
	}
}