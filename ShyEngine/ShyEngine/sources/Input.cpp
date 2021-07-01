#include <Input.h>
#include <iostream>

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
			this->quitting = true;
			break;

		case SDL_KEYDOWN:
			break;

		case SDL_KEYUP:
			break;

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
	this->quitting = false;
}

bool Input::isQuitting()
{
	return this->quitting;
}
