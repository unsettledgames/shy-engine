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

enum class GameState { GAME_STATE_RUNNING, GAME_STATE_PAUSED, GAME_STATE_STOPPED };

// 0x2 is used by SDL_WINDOW_OPENGL
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x4, BORDERLESS = 0x8 };

namespace ShyEngine 
{
	class SpriteRenderer;

	class _ShyEngine
	{
		private:
			SDL_Window* m_gameWindow = nullptr;
			SDL_GLContext m_glContext;

			GameState m_state = GameState::GAME_STATE_PAUSED;

			AudioEngine m_audioEngine;

			std::vector<System*> m_systems;
			std::vector<Entity> m_entities;
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

			int m_screenWidth;
			int m_screenHeight;

			void initShaders();

			void initSystems();

			void loop();

			void drawUI();

			// TEST
			Camera2D m_camera;
			Camera2D m_hudCamera;

			FpsLimiter m_fpsLimiter;
			float m_deltaTime = 0;

		public:
			_ShyEngine(unsigned int flags);

			~_ShyEngine();

			void createWindow(int width, int height, std::string name, unsigned int flags, unsigned int fps = 60);

			void run();

			int getScreenWidth() { return m_screenWidth; }

			int getScreenHeight() { return m_screenHeight; }

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

			void registerShader(ShaderProgram* toRegister);

			Entity* createEntity(const std::string& name = "NewEntity");

			float getFPS();

			float getDeltaTime() { return m_deltaTime; }

			Camera2D* getCamera() { return &m_camera; }
	};

	extern _ShyEngine Engine;
}
