#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Input.h>
#include <iostream>
#include <Error.h>
#include <Sprite.h>
#include <ShaderProgram.h>
#include <Utility.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <ResourcesManager.h>
#include <Timing.h>
#include <cstdlib>
#include <SpriteFont.h>

enum class GameState {GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED};

// 0x2 is used by SDL_WINDOW_OPENGL
enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x4, BORDERLESS = 0x8};

/*
	Window should probably renamed to Engine, as it contains all the components that make up the
	whole engine. Or (better) Engine and Window should be split into 2 different classes, I wonder if it's
	possible to have an Engine without a Window? I don't see the benefits tbh, so it's probably ok to
	put everything in the same class. Maybe the Engine could have a createWindow(width, height) method?
*/
namespace ShyEngine {
	class Window
	{
	private:
		SDL_Window* _gameWindow;
		SDL_GLContext _glContext;

		Input _input;

		GameState _state;
		ShaderProgram _colorShader;

		// TEST
		Camera2D _camera;
		SpriteBatch _spriteBatch;
		SpriteBatch _hudBatch;
		FpsLimiter _fpsLimiter;
		SpriteFont* _spriteFont;

		// REFACTOR: have a proper Time class
		float _time;

		// REFACTOR: Window attributes?
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
