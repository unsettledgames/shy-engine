#include <input/Input.h>
#include <iostream>

namespace ShyEngine {
	Input::Input()
	{
		clearInput();
	}

	Input::~Input()
	{

	}

	void Input::processInput()
	{
		SDL_Event inputEvent;

		// Clearing previous input events
		clearInput();

		// Polling for new events
		while (SDL_PollEvent(&inputEvent))
		{
			switch (inputEvent.type)
			{
				case SDL_MOUSEMOTION:
				{
					setMousePosition(inputEvent.motion.x, inputEvent.motion.y);
					break;
				}

				case SDL_QUIT:
				{
					this->m_quitting = true;
					break;
				}

				case SDL_KEYDOWN:
				{
					SDL_Keycode key = inputEvent.key.keysym.sym;
					std::unordered_map<SDL_Keycode, InputData>::iterator inputData = m_keysMap.find(key);
					InputData toAdd;

					if (inputData == m_keysMap.end())
					{
						toAdd.isDown = true;
						toAdd.startDownTime = SDL_GetTicks();
						toAdd.lastDownTime = toAdd.startDownTime;
						toAdd.upTime = 0;

						m_keysMap.insert(std::make_pair(key, toAdd));
					}
					else if (!inputData->second.isDown) 
					{
						inputData->second.isDown = true;
						inputData->second.startDownTime = SDL_GetTicks();
						inputData->second.lastDownTime = SDL_GetTicks();
						inputData->second.upTime = 0;
					}
					else 
					{
						inputData->second.lastDownTime = SDL_GetTicks();
					}

					break;
				}

				case SDL_KEYUP:
				{
					SDL_Keycode key = inputEvent.key.keysym.sym;
					std::unordered_map<SDL_Keycode, InputData>::iterator toUpdate = m_keysMap.find(key);

					toUpdate->second.isDown = false;
					toUpdate->second.upTime = SDL_GetTicks();

					m_lastKeyUp = key;

					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					Uint8 button = inputEvent.button.button;
					std::unordered_map<Uint8, InputData>::iterator inputData = m_mouseMap.find(button);
					InputData toAdd;

					if (inputData == m_mouseMap.end()) 
					{
						toAdd.isDown = true;
						toAdd.startDownTime = SDL_GetTicks();
						toAdd.lastDownTime = toAdd.startDownTime;
						toAdd.upTime = 0;

						m_mouseMap.insert(std::make_pair(button, toAdd));
					}
					else if (!inputData->second.isDown) 
					{
						inputData->second.isDown = true;
						inputData->second.startDownTime = SDL_GetTicks();
						inputData->second.lastDownTime = SDL_GetTicks();
						inputData->second.upTime = 0;
					}
					else 
					{
						inputData->second.lastDownTime = SDL_GetTicks();
					}
					
					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					Uint8 button = inputEvent.button.button;
					std::unordered_map<Uint8, InputData>::iterator toUpdate = m_mouseMap.find(button);

					toUpdate->second.isDown = false;
					toUpdate->second.upTime = SDL_GetTicks();

					m_lastButtonUp = inputEvent.button.button;
					break;
				}

				default:
					break;
			}
		}
	}

	void Input::clearInput()
	{
		this->m_quitting = false;

		this->m_lastKeyUp = -1;
		this->m_lastButtonUp = -1;
	}

	bool Input::isQuitting()
	{
		return this->m_quitting;
	}

	bool Input::getKeyDown(SDL_Keycode key)
	{
		return m_keysMap.find(key) != m_keysMap.end() &&
			m_keysMap.find(key)->second.isDown;
	}

	bool Input::getKeyUp(SDL_Keycode key)
	{
		return m_lastKeyUp != -1 && m_lastKeyUp == key;
	}

	bool Input::keyPressed(SDL_Keycode key)
	{
		auto keyIt = m_keysMap.find(key);

		if (keyIt != m_keysMap.end())
		{
			InputData data = keyIt->second;

			if (data.lastDownTime - data.startDownTime < INPUT_PRESSED_THRESHOLD)
				return true;
		}

		return false;
	}

	bool Input::getButtonDown(Uint8 button)
	{
		return m_mouseMap.find(button) != m_mouseMap.end() &&
			m_mouseMap.find(button)->second.isDown;
	}

	bool Input::getButtonUp(Uint8 button)
	{
		return m_lastButtonUp != -1 && m_lastButtonUp == button;
	}

	bool Input::buttonPressed(Uint8 button)
	{
		auto buttonIt = m_mouseMap.find(button);

		if (buttonIt != m_mouseMap.end())
		{
			InputData data = buttonIt->second;

			if (data.lastDownTime - data.startDownTime < INPUT_PRESSED_THRESHOLD)
				return true;
		}

		return false;
	}

	glm::vec2 Input::getMousePosition()
	{
		return this->m_mousePosition;
	}

	void Input::setMousePosition(float x, float y)
	{
		this->m_mousePosition.x = x;
		this->m_mousePosition.y = y;
	}
}