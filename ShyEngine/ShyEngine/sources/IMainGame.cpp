#include <IMainGame.h>
#include <Timing.h>

namespace ShyEngine
{
	void IMainGame::run()
	{
		if (!init())
			return;
		m_isRunning = true;

		while (true)
		{
			// GameLoop
		}
	}

	void IMainGame::exit()
	{
		
	}

	bool IMainGame::init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		return true;
	}
}