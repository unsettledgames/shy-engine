#include <engine/ShyEngine.h>

#include <engine/systems/Renderer.h>
#include <engine/systems/SpriteRenderer.h>

namespace ShyEngine {
	_ShyEngine Engine = _ShyEngine::_ShyEngine(SDL_INIT_EVERYTHING);

	_ShyEngine::_ShyEngine(unsigned int flags)
	{
		// Initializing SDL
		int sdlErr = SDL_Init(flags);

		// Enabling double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}

	_ShyEngine::~_ShyEngine() { }

	void _ShyEngine::initSystems()
	{
		// Place the HUD camera in the middle of the screen and don't move it
		m_hudCamera.init(m_screenWidth, m_screenHeight);
		m_hudCamera.setPosition(glm::vec2(0, 0));

		m_camera.init(m_screenWidth, m_screenHeight);
		m_camera.setScale(0.5);
		
		m_audioEngine.init();

		// Create the systems
		// Renderers
		m_spriteRenderer = new SpriteRenderer();
		m_textRenderer = new TextRenderer();
		m_particleRenderer = new ParticleRenderer();

		// Physics
		m_physicsManager = new PhysicsManager();
		m_collisionManager = new CollisionManager(50, glm::vec2(0, 0), glm::vec2(50, 50));
	}

	void _ShyEngine::createWindow(int width, int height, std::string name, unsigned int flags, unsigned int fps /*= 60*/)
	{
		m_screenWidth = width;
		m_screenHeight = height;

		// Initialize the FPS limiter with a value of fps: that alone won't make the engine limit fps, the user will
		// also have to call fpsLimiter.toggleFpsLimiting(true)
		m_fpsLimiter.init(fps);

		// Add SDL flags to the engine flags
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

		// IMPROVEMENT: let user decide v sync values, disabled atm
		SDL_GL_SetSwapInterval(0);
		// Enable alpha blending
		glEnable(GL_BLEND);
		// IMPROVEMENT: let the user decide blending mode
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Initialize the systems
		initSystems();

		//m_audioEngine.play((Music&)ResourcesManager.getMusic("sfx/6th.mp3"), 1);

		// Printing debug data
		std::cout << "CWD: " << Utility::getCwd() << std::endl;
		Utility::printOpenGLVersion();
	}

	void _ShyEngine::run()
	{
		// Start the system update loop
		this->m_state = GameState::GAME_STATE_RUNNING;		
		this->loop();
	}

	void _ShyEngine::loop()
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
			// This is used to simulate more steps in case of a high deltatime
			int currSimStep = 0;

			m_fpsLimiter.begin();
			// Delta time management ISSUE: it's always 0
			float totalDeltaTime = m_fpsLimiter.getDeltaTime();

			while (totalDeltaTime > 0.0f && currSimStep < MAX_SIM_STEPS)
			{
				// IMPROVEMENT: multiple cameras, the engine updates the active one
				m_camera.update();
				m_hudCamera.update();

				float deltaTime = std::min(MAX_DELTA_TIME, totalDeltaTime);

				// Prepare the data for the sprite and text renderer: the first uses the standard camera, the latter
				// uses the HUD camera
				ShaderData spriteRendererShaderData = { m_camera.getCameraMatrix(), m_camera.getViewportRect(), totalDeltaTime };
				ShaderData textRendererShaderData = { m_hudCamera.getCameraMatrix(), m_hudCamera.getViewportRect(), totalDeltaTime };
				// Prepare the data for the physics engine
				PhysicsData physicsData = { m_physicsManager->getGravity(), deltaTime };

				/*******************INPUT******************/
				// Processing input for this frame
				m_input.processInput();

				/********************PHYSICS******************/
				// Update loop for the physics and collision manager
				m_collisionManager->updateModules(physicsData);
				// DEBUG
				if (m_input.getKeyDown(SDLK_p))
				{
					m_physicsManager->updateModules(physicsData);
				}

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

				// TEST: W,A,S and D move the camera up, left, down, right
				if (m_input.getKeyDown(SDLK_w))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, 6.0f) * totalDeltaTime);
				if (m_input.getKeyDown(SDLK_s))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -6.0f) * totalDeltaTime);
				if (m_input.getKeyDown(SDLK_a))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(-6.0f, 0.0f) * totalDeltaTime);
				if (m_input.getKeyDown(SDLK_d))
					m_camera.setPosition(m_camera.getPosition() + glm::vec2(6.0f, 0.0f) * totalDeltaTime);

				totalDeltaTime -= deltaTime;
				currSimStep++;

				// Logging the fps every 10 iterations
				if (debugTime % 10 == 0)
					std::cout << "Fps: " << m_fpsLimiter.getCurrentFps() << std::endl;
				debugTime++;
			}

			m_fpsLimiter.end();
		}
	}

	void _ShyEngine::registerShader(ShaderProgram* toRegister)
	{
		// Simply add the shader to the list of shaders
		m_shaders.push_back(toRegister);
	}

	Entity* _ShyEngine::createEntity(const std::string& name/* = "NewEntity"*/)
	{
		Entity* ret = new Entity(name);

		// Set the self reference
		ret->m_reference = ret;
		// Set a new id for the entity
		ret->m_id = m_entityIdGenerator.get();

		return ret;
	}
}