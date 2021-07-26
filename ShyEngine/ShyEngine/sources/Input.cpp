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
					break;

				case SDL_QUIT:
				{
					this->_quitting = true;
					break;
				}

				case SDL_KEYDOWN:
				{
					SDL_Keycode key = inputEvent.key.keysym.sym;
					std::map<SDL_Keycode, InputData>::iterator inputData = _inputMap.find(key);
					InputData toAdd;

					if (inputData == _inputMap.end())
						toAdd = { true, SDL_GetTicks(), SDL_GetTicks(), 0 };
					else if (!inputData->second.isDown) {
						inputData->second.isDown = true;
						inputData->second.startDownTime = SDL_GetTicks();
						inputData->second.lastDownTime = SDL_GetTicks();
						inputData->second.upTime = 0;
					}
					else {
						inputData->second.lastDownTime = SDL_GetTicks();
					}

					_inputMap.insert(std::make_pair(key, toAdd));

					break;
				}

				case SDL_KEYUP:
				{
					SDL_Keycode key = inputEvent.key.keysym.sym;
					std::map<SDL_Keycode, InputData>::iterator toUpdate = _inputMap.find(key);

					toUpdate->second.isDown = false;
					toUpdate->second.upTime = SDL_GetTicks();

					break;
				}

				case SDL_MOUSEBUTTONDOWN:
					break;

				case SDL_MOUSEBUTTONUP:
					break;

				default:
					std::cout << "Unhandled input event with type " << inputEvent.type << std::endl;
					break;
			}
		}
	}

	void Input::clearInput()
	{
		this->_quitting = false;
	}

	bool Input::isQuitting()
	{
		return this->_quitting;
	}

	bool Input::keyPressed(SDL_Keycode key)
	{
		return false;
	}

	bool Input::getKeyDown(SDL_Keycode key)
	{
		return _inputMap.find(key) != _inputMap.end() &&
			_inputMap.find(key)->second.isDown;
	}

	bool Input::getKeyUp(SDL_Keycode key)
	{
		return _inputMap.find(key) == _inputMap.end() ||
			!_inputMap.find(key)->second.isDown;
	}
}