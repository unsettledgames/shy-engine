#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

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

			// OPTIMIZABLE? Both SDL_Keycode and Uint8 are unsigned ints, so I could just have a single 
			// map. Maybe research a little bit to understand if it's worth it
			// Used to save the state of keys
			std::unordered_map<SDL_Keycode, InputData> _keysMap;
			// Used to save the state of mouse buttons
			std::unordered_map<Uint8, InputData> _mouseMap;

			// The key that has been released in the current frame (-1 if none)
			SDL_Keycode _lastKeyUp;
			// The button that has been released in the current frame (-1 if none)
			Uint8 _lastButtonUp;

			// Current mouse position
			glm::vec2 _mousePosition;

			void setMousePosition(float x, float y);

		public:
			Input();

			~Input();

			void clearInput();

			void processInput();

			bool isQuitting();

			bool getKeyDown(SDL_Keycode key);

			bool getKeyUp(SDL_Keycode key);

			bool getButtonDown(Uint8 button);

			bool getButtonUp(Uint8 button);

			glm::vec2 getMousePosition();

	};
}