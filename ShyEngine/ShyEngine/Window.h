#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Input.h>
#include <Renderer.h>
#include <iostream>
#include <Error.h>
#include <Sprite.h>
#include <ShaderProgram.h>
#include <Utility.h>
#include <Camera2D.h>

enum class GameState {GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED};

// 0x2 is used by SDL_WINDOW_OPENGL
enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x4, BORDERLESS = 0x8};

namespace ShyEngine {
	class Window
	{
	private:
		SDL_Window* _gameWindow;

		Input _input;
		Renderer _renderer;

		GameState _state;
		ShaderProgram _colorShader;

		// TEST
		Camera2D _camera;

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

		void init(std::string windowName, unsigned int flags);

		void run();

		void calculateFPS();

		int getScreenWidth();

		int getScreenHeight();
	};
}
