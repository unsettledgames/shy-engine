#include <window/Window.h>

namespace ShyEngine {
	Window::Window(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

	void Window::run()
	{
		this->m_state = GameState::GAME_STATE_RUNNING;

		m_camera.init(m_width, m_height);
		m_hudCamera.init(m_width, m_height);
		m_hudCamera.setPosition(glm::vec2(0, 0));

		this->loop();
	}

	void Window::loop()
	{
		static int frameCounter = 1;
		const int MAX_SIM_STEPS = 6;
		const float MAX_DELTA_TIME = 1.0f;

		// Running the engine loop until the user doesn't quit
		while (this->m_state == GameState::GAME_STATE_RUNNING)
		{
			int currSimStep = 0;
			m_fpsLimiter.begin();

			// Processing input for this frame
			m_input.processInput();
			
			// Setting up the shader REFACTOR: put this in the SpriteRenderer class
			m_colorShader.use(m_time);
			// REFACTOR: since the shader will be a SpriteRenderer property, I should find a way
			// to pass camera data to it. Or maybe have a currentShader in the Engine? Even though
			// conceptually, shaders are linked to Rendering
			m_colorShader.setOrthoProjection("orthoProj", m_camera.getCameraMatrix());

			// Clearing buffers REFACTOR: Renderer?
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 1, 1);

			// REFACTOR: delta time implementation: uncomment it and put rendering and physics 
			// code inside of the while
			/*
			float totalDeltaTime = _fpsLimiter.getDeltaTime();
			while (totalDeltaTime > 0.0f && currSimStep < MAX_SIM_STEPS)
			{
				float deltaTime = std::min(MAX_DELTA_TIME, deltaTime);

				// Update stuff, pass deltaTime to them

				totalDeltaTime -= deltaTime;
				currSimStep++;
			}
			*/

			// REFACTOR: this is probably part of Renderer as well
			m_spriteBatch.begin();
			ColorRGBA8 col = { 255, 255, 255, 255 };
			//GLuint tex = ResourcesManager::getTexture("textures/5heartsSmall.png").id;
			GLuint tex = ResourcesManager::getTexture("textures/Alice.png").id;
			// TEST
			m_spriteBatch.draw(glm::vec4(0, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col, 0.785398f);
			m_spriteBatch.draw(glm::vec4(200, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col);
			m_spriteBatch.draw(glm::vec4(400, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col);

			m_spriteBatch.end();
			m_spriteBatch.render();

			if (m_input.getKeyDown(SDLK_p))
				m_testParticleBatch->addParticle(glm::vec2(100, 100), ColorRGBA8(255, 0, 255, 255), glm::vec2(1.0f, 1.0f), glm::vec2(50.0f, 50.0f));
			m_particleEngine.draw(&m_spriteBatch);

			// TEST: draws the HUD
			drawUI();

			// Camera update REFACTOR: the camera should update on its own, in some way. Maybe the
			// enine has an active camera and it updates it?
			m_camera.update();
			m_hudCamera.update();
			m_particleEngine.update();

			// Cleanup
			SDL_GL_SwapWindow(this->m_gameWindow);
			m_colorShader.unuse();

			// If the user decided to quit, I stop the loop
			if (m_input.isQuitting())
				this->m_state = GameState::GAME_STATE_STOPPED;

			// TEST
			if (m_input.getKeyDown(SDLK_w))
				m_camera.setPosition(m_camera.getPosition() + glm::vec2(0, 0.5f));

			m_fpsLimiter.end();
		}
	}

	void Window::drawUI()
	{
		glm::mat4 projMatrix = m_hudCamera.getCameraMatrix();
		GLint pUniform = m_colorShader.getUniformLocation("orthoProj");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projMatrix[0][0]);

		m_hudBatch.begin();

		m_spriteFont->draw(m_hudBatch, "abcdefghijklmnopqrstuvwxyz1234567890", glm::vec2(0, 0), glm::vec2(1, 1), 1.0f,
			ColorRGBA8(255, 255, 255, 255));

		m_hudBatch.end();
		m_hudBatch.render();
	}

	void Window::init(std::string windowName, unsigned int flags)
	{

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
		this->m_gameWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_width, this->m_height, flags);

		if (m_gameWindow == nullptr)
			Error::fatal("Couldn't create the main window.");

		// Initializing opengl
		this->m_glContext = SDL_GL_CreateContext(m_gameWindow);
		if (this->m_glContext == nullptr)
			Error::fatal("Couldn't create GL context");
		// Clearing input
		this->m_input.clearInput();

		// Initializing glew
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();

		if (err == GLEW_OK)
			std::cout << ("Initialized Glew") << std::endl;
		else
			Error::fatal("Couldn't initialize Glew");

		SDL_GL_SetSwapInterval(0);	// IMPROVEMENT: let user decide v sync values, disabled atm
		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// IMPROVEMENT: let the user decide blending mode
		// Initializing shaders
		initShaders();

		// TEST
		m_audioEngine.init();
		m_spriteBatch.init();
		m_hudBatch.init();
		m_spriteFont = new SpriteFont("fonts/04.TTF", 16);

		//m_audioEngine.loadSoundEffect("sfx/wub.ogg").play();

		m_testParticleBatch = new ParticleBatch2D();
		m_testParticleBatch->init(1000, 0.01f, ResourcesManager::getTexture("textures/particle.png"));
		m_particleEngine.addParticleBatch(m_testParticleBatch);

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

		// Printing debug data
		std::cout << "CWD: " << Utility::getCwd() << std::endl;
		Utility::printOpenGLVersion();
	}

	void Window::initShaders()
	{
		m_colorShader.compileShaders("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");
		m_colorShader.addAttribute("vertPos");
		m_colorShader.addAttribute("vertColor");
		m_colorShader.addAttribute("vertUV");
		m_colorShader.linkShaders();
	}

	int Window::getScreenHeight()
	{
		return this->m_height;
	}

	int Window::getScreenWidth()
	{
		return this->m_width;
	}
}