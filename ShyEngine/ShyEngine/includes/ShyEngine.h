#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <string>

#include <screen/IGameScreen.h>
#include <input/Input.h>
#include <iostream>
#include <util/Error.h>
#include <rendering/Sprite.h>
#include <rendering/ShaderProgram.h>
#include <util/Utility.h>
#include <rendering/Camera2D.h>
#include <rendering/SpriteBatch.h>
#include <data/ResourcesManager.h>
#include <input/EventBus.h>
#include <timing/Timing.h>
#include <cstdlib>
#include <ui/SpriteFont.h>
#include <audio/AudioEngine.h>
#include <rendering/ParticleEngine2D.h>
#include <rendering/ParticleBatch2D.h>
#include <box2d/box2d.h>
#include <memory>
#include <physics/Box.h>

enum class GameState { GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED };

// 0x2 is used by SDL_WINDOW_OPENGL
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x4, BORDERLESS = 0x8 };

namespace ShyEngine {
	class ShyEngine
	{
		private:
			SDL_Window* m_gameWindow = nullptr;
			SDL_GLContext m_glContext;

			std::vector<IGameScreen> m_screens;

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

			int m_screenWidth;
			int m_screenHeight;

			void initShaders();

			void loop();

			void drawUI();

		public:
			ShyEngine(unsigned int flags);

			~ShyEngine();

			void createWindow(int width, int height, std::string name, unsigned int flags, unsigned int fps = 60);

			void run();

			int getScreenWidth() { return m_screenWidth; }

			int getScreenHeight() { return m_screenHeight; }
	};
}
