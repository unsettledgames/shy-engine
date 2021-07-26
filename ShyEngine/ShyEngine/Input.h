#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <map>

namespace ShyEngine {
	typedef struct inputdata{
		bool isDown;
		
		unsigned int startDownTime;
		unsigned int lastDownTime;
		unsigned int upTime;
	} InputData;

	class Input
	{
		private:
			bool _quitting;
			std::map<SDL_Keycode, InputData> _inputMap;

		public:
			Input();

			~Input();

			void clearInput();

			void processInput();

			bool isQuitting();

			bool keyPressed(SDL_Keycode key);

			bool getKeyDown(SDL_Keycode key);

			bool getKeyUp(SDL_Keycode key);

	};
}