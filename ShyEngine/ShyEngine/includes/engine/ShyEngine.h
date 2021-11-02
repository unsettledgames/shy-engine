#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <memory>

#include <input/Input.h>
#include <input/EventBus.h>
#include <engine/Settings.h>

#include <util/Error.h>
#include <util/Utility.h>
#include <util/Classes.h>
#include <timing/Timing.h>
#include <util/IdGenerator.h>

#include <data/ResourcesManager.h>

#include <rendering/ShaderProgram.h>
#include <rendering/Camera2D.h>

#include <audio/AudioEngine.h>

#include <engine/System.h>
#include <engine/Entity.h>

#include <engine/modules/Sprite.h>
#include <engine/modules/Text.h>
#include <engine/modules/ParticleSystem.h>

#include <engine/modules/UserScript.h>

#include <engine/modules/Physics.h>
#include <engine/modules/collisions/Collider2D.h>
#include <engine/modules/collisions/CircleCollider2D.h>
#include <engine/modules/collisions/RectCollider2D.h>

#include <engine/systems/SpriteRenderer.h>
#include <engine/systems/ParticleRenderer.h>
#include <engine/systems/TextRenderer.h>
#include <engine/systems/PhysicsManager.h>
#include <engine/systems/CollisionManager.h>
#include <engine/systems/UserScriptsManager.h>

/*
	\brief	Used to store the current state of the game
*/
enum class GameState { GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED };

// 0x2 is used by SDL_WINDOW_OPENGL
// REFACTOR: just use opengl flags or use aliases?
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x4, BORDERLESS = 0x8 };

namespace ShyEngine 
{
	class SpriteRenderer;

	/*
		\brief	The whole freaking engine core. Initializes all the third party libraries (such as Glew or SDL) and
				takes care of the engine loop.

				The engine loop updates all the systems, computes deltaTime and the current FPS. It also gives methods
				to register modules and shaders created by the user so that it's possible to use them.
	*/
	class _ShyEngine
	{
		private:
			// The game window
			SDL_Window* m_gameWindow = nullptr;
			// We need to create a context to draw
			SDL_GLContext m_glContext;

			// Curent game state
			GameState m_state = GameState::GAME_STATE_PAUSED;

			// Audio engine: takes care of all the audio-related functions. REFACTOR: make it globally accessible?
			AudioEngine m_audioEngine;

			// All the systems of the engine. UNUSED
			std::vector<System*> m_systems;
			// All the entities in the game. UNUSED
			std::vector<Entity> m_entities;
			// All the shaders registered by th user
			std::vector<ShaderProgram*> m_shaders;

			// ID generators
			IdGenerator m_entityIdGenerator;

			// Managers
			PhysicsManager* m_physicsManager;
			CollisionManager* m_collisionManager;
			UserScriptsManager* m_scriptsManager;

			// Renderers
			SpriteRenderer* m_spriteRenderer;
			TextRenderer* m_textRenderer;
			ParticleRenderer* m_particleRenderer;

			// Window resolution
			int m_screenWidth;
			int m_screenHeight;

			/*
				\brief	Initializes all the ShyEngine systems and engines.
			*/
			void initSystems();

			/*
				\brief	Engine loop.
						- Computes delta time and current FPS
						- Simulates physics, takes care of collisions
						- Renders renderable objects depending on their data
						- Updates cameras
			*/
			void loop();

			// Main camera. IMPROVEMENT: add custom cameras
			Camera2D m_camera;
			// Camera used to render the UI (text)
			Camera2D m_hudCamera;

			// Calculates and limits the FPS of the game if necessary
			FpsLimiter m_fpsLimiter;
			// Current delta time
			float m_deltaTime = 0;

		public:
			/*
				\brief	Creates the engine and initializes SDL depending on the flags

				\param	flags	The flags used to initialize SDL
			*/
			_ShyEngine(unsigned int flags);

			~_ShyEngine();

			/*
				\brief	Creates a game window using the flags passed as an argument.
					- Initializes the FPSLimiter
					- Initializes OpenGL and Glew
					- Sets some OpenGL options
					- Initializes the systems using initSystems
			*/
			void createWindow(int width, int height, std::string name, unsigned int flags, unsigned int fps = 60);

			/*
				\brief	Starts the game loop and calls the init functions of the custom scripts.
			*/
			void run();

			/*
				\brief	Registers a Module so that the engine can update it. Depending on the ModuleType, the module
						is assigned to a system that will take care of it during the engine loop.

				\param	toRegister	The Module to register to the engine.
			*/
			template <class ModuleType>
			void registerModule(ModuleType* toRegister)
			{
				toRegister->m_reference = toRegister;
				// REFACTOR: turn name into a type so it's less flexible
				if (toRegister->IsClassType(Sprite::Type))
				{
					m_spriteRenderer->addModule(dynamic_cast<Sprite*>(toRegister));
				}
				else if (toRegister->IsClassType(Text::Type))
				{
					m_textRenderer->addModule(dynamic_cast<Text*>(toRegister));
				}
				else if (toRegister->IsClassType(ParticleSystem::Type))
				{
					m_particleRenderer->addModule(dynamic_cast<ParticleSystem*>(toRegister));
				}
				else if (toRegister->IsClassType(Physics::Type))
				{
					m_physicsManager->addModule(dynamic_cast<Physics*>(toRegister));
				}
				else if (toRegister->IsClassType(CircleCollider2D::Type))
				{
					m_collisionManager->addModule(dynamic_cast<CircleCollider2D*>(toRegister));
				}
				else if (toRegister->IsClassType(RectCollider2D::Type))
				{
					m_collisionManager->addModule(dynamic_cast<RectCollider2D*>(toRegister));
				}
				else if (toRegister->IsClassType(UserScript::Type))
				{
					m_scriptsManager->addModule(dynamic_cast<UserScript*>(toRegister));
				}
			}

			/*
				UNUSED
			*/
			void registerShader(ShaderProgram* toRegister);

			/*
				\brief	Creates an entity. This is necessary because the engine sets both the entity reference
						(REFACTOR: this could be done in the Entity constructor) and its id (REFACTOR: this could
						be done with a static id generator in the entity class, which would make this method
						completely useless).
			*/
			Entity* createEntity(const std::string& name = "NewEntity");

			float getFPS();
			float getDeltaTime() { return m_deltaTime; }
			int getScreenWidth() { return m_screenWidth; }
			int getScreenHeight() { return m_screenHeight; }
			Camera2D* getCamera() { return &m_camera; }
	};

	extern _ShyEngine Engine;
}
