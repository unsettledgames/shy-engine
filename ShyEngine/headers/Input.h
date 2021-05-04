#pragma once

#include <SDL/SDL.h>

class Input
{
private:
	bool quitting;

public:
	Input();

	~Input();

	void clearInput();

	void processInput();

	bool isQuitting();
};
