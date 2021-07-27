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
#include <SpriteBatch.h>
#include <ResourcesManager.h>
#include <Timing.h>

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
		SpriteBatch _spriteBatch;
		FpsLimiter _fpsLimiter;

		float _time;

		int _width;
		int _height;

		void initShaders();

		void loop();

	public:
		Window(int width, int height);

		void init(std::string windowName, unsigned int flags);

		void run();

		int getScreenWidth();

		int getScreenHeight();
	};
}
