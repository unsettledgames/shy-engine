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

enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};

namespace ShyEngine {
	class Window
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

		void initShaders();

		void loop();

	public:
		Window(int width, int height);

		~Window();

		void init(std::string windowName, unsigned int flags);

		void run();

		void calculateFPS();

		int getScreenWidth();

		int getScreenHeight();
	};
}
