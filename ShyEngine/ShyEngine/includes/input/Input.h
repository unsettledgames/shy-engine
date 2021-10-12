#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#define INPUT_PRESSED_THRESHOLD	5

namespace ShyEngine {
	typedef struct inputdata{
		bool isDown;
		
		unsigned int startDownTime;
		unsigned int lastDownTime;
		unsigned int upTime;
	} InputData;

	class _Input
	{
		private:
			bool m_quitting;

			// OPTIMIZABLE? Both SDL_Keycode and Uint8 are unsigned ints, so I could just have a single 
			// map. Maybe research a little bit to understand if it's worth it <- definitely merge them,
			// it'll make you save quite a lot of lines of code
			// Used to save the state of keys
			std::unordered_map<SDL_Keycode, InputData> m_keysMap;
			// Used to save the state of mouse buttons
			std::unordered_map<Uint8, InputData> m_mouseMap;

			// The key that has been released in the current frame (-1 if none)
			SDL_Keycode m_lastKeyUp;
			// The button that has been released in the current frame (-1 if none)
			Uint8 m_lastButtonUp;

			// Current mouse position
			glm::vec2 m_mousePosition;

			void setMousePosition(float x, float y);

		public:
			_Input();

			~_Input();

			void clearInput();

			void processInput();

			bool isQuitting();

			bool getKeyDown(SDL_Keycode key);

			bool getKeyUp(SDL_Keycode key);

			bool keyPressed(SDL_Keycode key);

			bool getButtonDown(Uint8 button);

			bool getButtonUp(Uint8 button);
			
			bool buttonPressed(Uint8 button);

			glm::vec2 getMousePosition();

	};

	extern _Input Input;
}