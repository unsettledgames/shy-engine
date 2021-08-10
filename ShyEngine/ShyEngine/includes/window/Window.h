#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <input/Input.h>
#include <iostream>
#include <util/Error.h>
#include <rendering/Sprite.h>
#include <rendering/ShaderProgram.h>
#include <util/Utility.h>
#include <rendering/Camera2D.h>
#include <rendering/SpriteBatch.h>
#include <data/ResourcesManager.h>
#include <timing/Timing.h>
#include <cstdlib>
#include <ui/SpriteFont.h>
#include <audio/AudioEngine.h>
#include <rendering/ParticleEngine2D.h>
#include <rendering/ParticleBatch2D.h>
#include <box2d/box2d.h>
#include <memory>
#include <physics/Box.h>

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
		SDL_Window* m_gameWindow = nullptr;
		SDL_GLContext m_glContext;

		Input m_input;

		GameState m_state = GameState::GAME_STATE_PAUSED;
		ShaderProgram m_colorShader;

		// TEST
		Camera2D m_camera;
		Camera2D m_hudCamera;

		SpriteBatch m_spriteBatch;
		SpriteBatch m_hudBatch;

		FpsLimiter m_fpsLimiter;
		SpriteFont* m_spriteFont;

		AudioEngine m_audioEngine;
		ParticleEngine2D m_particleEngine;
		ParticleBatch2D* m_testParticleBatch = nullptr;

		std::unique_ptr<b2World> m_world;

		// REFACTOR: have a proper Time class
		float m_time = 0;

		// REFACTOR: Window attributes?
		int m_width;
		int m_height;

		void initShaders();

		void loop();

		void drawUI();

	public:
		Window(int width, int height);

		void init(std::string windowName, unsigned int flags);

		void run();

		int getScreenWidth();

		int getScreenHeight();
	};
}
