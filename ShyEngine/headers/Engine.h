#pragma once

#include <SDL/SDL.h>
#include <Input.h>
#include <Renderer.h>
#include <iostream>
#include <Error.h>
#include <Sprite.h>

enum class GameState {GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED};

class Engine
{
private:
	SDL_Window* _gameWindow;

	Input _input;
	Renderer _renderer;

	GameState _state;
	

	int _width;
	int _height;

	void init();

	void loop();

public:
	Engine(int width, int height);

	~Engine();

	void run();
	
};

