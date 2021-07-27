#include <Input.h>
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
					this->_quitting = true;
					break;
				}

				case SDL_KEYDOWN:
				{
					SDL_Keycode key = inputEvent.key.keysym.sym;
					std::unordered_map<SDL_Keycode, InputData>::iterator inputData = _keysMap.find(key);
					InputData toAdd;

					if (inputData == _keysMap.end())
					{
						toAdd.isDown = true;
						toAdd.startDownTime = SDL_GetTicks();
						toAdd.lastDownTime = toAdd.startDownTime;
						toAdd.upTime = 0;

						_keysMap.insert(std::make_pair(key, toAdd));
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
					std::unordered_map<SDL_Keycode, InputData>::iterator toUpdate = _keysMap.find(key);

					toUpdate->second.isDown = false;
					toUpdate->second.upTime = SDL_GetTicks();

					_lastKeyUp = key;

					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					Uint8 button = inputEvent.button.button;
					std::unordered_map<Uint8, InputData>::iterator inputData = _mouseMap.find(button);
					InputData toAdd;

					if (inputData == _mouseMap.end()) 
					{
						toAdd.isDown = true;
						toAdd.startDownTime = SDL_GetTicks();
						toAdd.lastDownTime = toAdd.startDownTime;
						toAdd.upTime = 0;

						_mouseMap.insert(std::make_pair(button, toAdd));
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
					std::unordered_map<Uint8, InputData>::iterator toUpdate = _mouseMap.find(button);

					toUpdate->second.isDown = false;
					toUpdate->second.upTime = SDL_GetTicks();

					_lastButtonUp = inputEvent.button.button;
					break;
				}

				default:
					break;
			}
		}
	}

	void Input::clearInput()
	{
		this->_quitting = false;

		this->_lastKeyUp = -1;
		this->_lastButtonUp = -1;
	}

	bool Input::isQuitting()
	{
		return this->_quitting;
	}

	bool Input::getKeyDown(SDL_Keycode key)
	{
		return _keysMap.find(key) != _keysMap.end() &&
			_keysMap.find(key)->second.isDown;
	}

	bool Input::getKeyUp(SDL_Keycode key)
	{
		return _lastKeyUp != -1 && _lastKeyUp == key;
	}

	bool Input::getButtonDown(Uint8 button)
	{
		return _mouseMap.find(button) != _mouseMap.end() &&
			_mouseMap.find(button)->second.isDown;
	}

	bool Input::getButtonUp(Uint8 button)
	{
		return _lastButtonUp != -1 && _lastButtonUp == button;
	}

	glm::vec2 Input::getMousePosition()
	{
		return this->_mousePosition;
	}

	void Input::setMousePosition(float x, float y)
	{
		this->_mousePosition.x = x;
		this->_mousePosition.y = y;
	}
}