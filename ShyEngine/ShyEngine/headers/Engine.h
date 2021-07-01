#pragma once

#include <SDL/SDL.h>
#include <Input.h>
#include <Renderer.h>
#include <iostream>
#include <Error.h>
#include <Sprite.h>
#include <ShaderProgram.h>
#include <Utility.h>

enum class GameState {GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED};

class Engine
{
private:
	SDL_Window* _gameWindow;

	Input _input;
	Renderer _renderer;

	GameState _state;
	ShaderProgram _colorShader;
	
	float _time;

	int _width;
	int _height;

	float _fps;
	float _maxFPS;
	float _frameTime;

	void init();

	void initShaders();

	void loop();

public:
	Engine(int width, int height);

	~Engine();

	void run();

	void calculateFPS();
	
};

