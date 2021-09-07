#include <engine/ShyEngine.h>

#include <engine/systems/Renderer.h>
#include <engine/systems/SpriteRenderer.h>

namespace ShyEngine {
	ShyEngine::ShyEngine(unsigned int flags)
	{
		// Initializing SDL
		int sdlErr = SDL_Init(flags);

		// Enabling double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}

	ShyEngine::~ShyEngine() { }

	void ShyEngine::initSystems()
	{
		m_hudCamera.init(m_screenWidth, m_screenHeight);
		m_hudCamera.setPosition(glm::vec2(0, 0));

		m_camera.init(m_screenWidth, m_screenHeight);
		m_audioEngine.init();

		m_spriteRenderer = new SpriteRenderer();
		m_textRenderer = new TextRenderer();
		m_particleRenderer = new ParticleRenderer();

		m_physicsManager = new PhysicsManager();
		m_collisionManager = new CollisionManager();
	}

	void ShyEngine::createWindow(int width, int height, std::string name, unsigned int flags, unsigned int fps /*= 60*/)
	{
		m_screenWidth = width;
		m_screenHeight = height;
		m_fpsLimiter.init(fps);

		if (flags & WindowFlags::INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		else if (flags & WindowFlags::FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		else if (flags & WindowFlags::BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		// Creating the game window
		this->m_gameWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, this->m_screenWidth, this->m_screenHeight, flags);
		if (m_gameWindow == nullptr)
			Error::fatal("Couldn't create the " + name + " window.");

		// Initializing opengl
		this->m_glContext = SDL_GL_CreateContext(m_gameWindow);
		if (this->m_glContext == nullptr)
			Error::fatal("Couldn't create GL context");
		
		// Start with a clean input handler
		this->m_input.clearInput();

		// Initializing glew
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();

		if (err == GLEW_OK)
			std::cout << ("Initialized Glew") << std::endl;
		else
			Error::fatal("Couldn't initialize Glew");

		// VSYNCIMPROVEMENT: let user decide v sync values, disabled atm
		SDL_GL_SetSwapInterval(0);
		// Enable alpha blending
		glEnable(GL_BLEND);
		// IMPROVEMENT: let the user decide blending mode
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Initialize the systems
		initSystems();

		//m_audioEngine.play((Music&)ResourcesManager.getMusic("sfx/6th.mp3"), 1);
/*
		// TEST PHYSICS MANAGEMENT
		// Create the physics world
		m_world = std::make_unique<b2World>(b2Vec2(0.0f, -9.81f));

		// Create the ground
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
		// Ground fixture
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);

		// Create a few boxes
		Box newBox;
		newBox.init(m_world.get(), glm::vec2(0.0f, 14.0f), glm::vec2(15.0f, 15.0f));
		*/
		// Printing debug data
		std::cout << "CWD: " << Utility::getCwd() << std::endl;
		Utility::printOpenGLVersion();
	}

	void ShyEngine::run()
	{
		this->m_state = GameState::GAME_STATE_RUNNING;		

		this->loop();
	}

	void ShyEngine::loop()
	{
		// Debugger time
		static int debugTime = 0;

		// Delta time
		static int frameCounter = 1;
		const int MAX_SIM_STEPS = 6;
		const float MAX_DELTA_TIME = 1.0f;

		// Running the engine loop until the user doesn't quit
		while (this->m_state == GameState::GAME_STATE_RUNNING)
		{
			int currSimStep = 0;

			m_fpsLimiter.begin();
			// Delta time management ISSUE: it's always 0
			float totalDeltaTime = m_fpsLimiter.getDeltaTime();

			while (totalDeltaTime > 0.0f && currSimStep < MAX_SIM_STEPS)
			{
				// Camera update REFACTOR: the camera should update on its own, in some way. Maybe the
				// engine has an active camera and it updates it?
				m_camera.update();
				m_hudCamera.update();

				float deltaTime = std::min(MAX_DELTA_TIME, totalDeltaTime);
				ShaderData spriteRendererShaderData = { m_camera.getCameraMatrix(), m_camera.getViewportRect(), totalDeltaTime };
				ShaderData textRendererShaderData = { m_hudCamera.getCameraMatrix(), m_hudCamera.getViewportRect(), totalDeltaTime };
				PhysicsData physicsData = { m_physicsManager->getGravity(), deltaTime };

				/*******************INPUT******************/
				// Processing input for this frame
				m_input.processInput();

				/********************PHYSICS******************/
				// Update loop for the physics and collision manager
				m_collisionManager->updateModules(physicsData);
				if (m_input.getKeyDown(SDLK_p))
					m_physicsManager->updateModules(physicsData);

				/********************RENDERING****************/
				glClearDepth(1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(0, 0, 1, 1);

				// Update loop for the sprite renderer
				m_spriteRenderer->updateModules(spriteRendererShaderData);
				// Update loop for the particle renderer
				m_particleRenderer->updateModules(spriteRendererShaderData);
				// Update loop for the text renderer
				m_textRenderer->updateModules(textRendererShaderData);

				// Cleanup
				SDL_GL_SwapWindow(this->m_gameWindow);

				// If the user decided to quit, I stop the loop
				if (m_input.isQuitting())
					this->m_state = GameState::GAME_STATE_STOPPED;

				// TEST
				if (m_input.getKeyDown(SDLK_w))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, 3.0f) * totalDeltaTime);
				if (m_input.getKeyDown(SDLK_s))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -3.0f) * totalDeltaTime);
				if (m_input.getKeyDown(SDLK_a))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(-3.0f, 0.0f) * totalDeltaTime);
				if (m_input.getKeyDown(SDLK_d))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(3.0f, 0.0f) * totalDeltaTime);

				totalDeltaTime -= deltaTime;
				currSimStep++;
			}

			if (debugTime % 100 == 0)
				std::cout << "Fps: " << m_fpsLimiter.getCurrentFps() << std::endl;
			m_fpsLimiter.end();

			debugTime++;
		}
	}

	void ShyEngine::registerModule(Module* toRegister)
	{
		toRegister->m_reference = toRegister;
		// REFACTOR: turn name into a type so it's less flexible
		if (toRegister->getName().compare("Sprite") == 0)
		{
			m_spriteRenderer->addModule(dynamic_cast<Sprite*>(toRegister));
		}
		else if (toRegister->getName().compare("Text") == 0)
		{
			m_textRenderer->addModule(dynamic_cast<Text*>(toRegister));
		}
		else if (toRegister->getName().compare("ParticleSystem") == 0)
		{
			m_particleRenderer->addModule(dynamic_cast<ParticleSystem*>(toRegister));
		}
		else if (toRegister->getName().compare("Physics") == 0)
		{
			m_physicsManager->addModule(dynamic_cast<Physics*>(toRegister));
		}
		else if (toRegister->getName().find("Collider") != std::string::npos)
		{
			m_collisionManager->addModule(dynamic_cast<Collider2D*>(toRegister));
		}
	}

	void ShyEngine::registerShader(ShaderProgram* toRegister)
	{
		m_shaders.push_back(toRegister);
	}

	Entity* ShyEngine::createEntity(const std::string& name/* = "NewEntity"*/)
	{
		Entity* ret = new Entity(name);
		ret->m_reference = ret;

		return ret;
	}
}