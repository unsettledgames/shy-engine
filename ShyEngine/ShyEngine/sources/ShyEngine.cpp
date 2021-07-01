#include <ShyEngine.h>

namespace ShyEngine {
	ShyEngine::ShyEngine()
	{
		init();
	}

	ShyEngine::~ShyEngine()
	{

	}

	void ShyEngine::init()
	{
		// Initializing SDL
		int sdlErr = SDL_Init(SDL_INIT_EVERYTHING);

		// Enabling double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
}