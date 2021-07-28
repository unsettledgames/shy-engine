#include <Window.h>

namespace ShyEngine {
	Window::Window(int width, int height) :
		_width(width), _height(height), _time(0), _state(GameState::GAME_STATE_PAUSED), _gameWindow(nullptr)
	{
	}

	void Window::run()
	{
		this->_state = GameState::GAME_STATE_RUNNING;

		_camera.init(_width, _height);

		this->loop();
	}

	void Window::loop()
	{
		static int frameCounter = 1;
		const int MAX_SIM_STEPS = 6;
		const float MAX_DELTA_TIME = 1.0f;

		// Running the engine loop until the user doesn't quit
		while (this->_state == GameState::GAME_STATE_RUNNING)
		{
			int currSimStep = 0;
			_fpsLimiter.begin();

			// Processing input for this frame
			_input.processInput();
			
			// Setting up the shader REFACTOR: put this in the SpriteRenderer class
			_colorShader.use(_time);
			// REFACTOR: since the shader will be a SpriteRenderer property, I should find a way
			// to pass camera data to it. Or maybe have a currentShader in the Engine? Even though
			// conceptually, shaders are linked to Rendering
			_colorShader.setOrthoProjection("orthoProj", _camera.getCameraMatrix());

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
			_spriteBatch.begin();
			ColorRGBA8 col = { 255, 255, 255, 255 };
			//GLuint tex = ResourcesManager::getTexture("textures/5heartsSmall.png").id;
			GLuint tex = ResourcesManager::getTexture("textures/Alice.png").id;
			// TEST
			_spriteBatch.draw(glm::vec4(0, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col);
			_spriteBatch.draw(glm::vec4(200, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col);
			_spriteBatch.draw(glm::vec4(400, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col);

			_spriteBatch.end();
			_spriteBatch.render();

			// Camera update REFACTOR: the camera should update on its own, in some way. Maybe the
			// enine has an active camera and it updates it?
			_camera.update();

			// Cleanup
			SDL_GL_SwapWindow(this->_gameWindow);
			_colorShader.unuse();

			// If the user decided to quit, I stop the loop
			if (_input.isQuitting())
				this->_state = GameState::GAME_STATE_STOPPED;

			// TEST
			if (_input.getKeyDown(SDLK_w))
				_camera.setPosition(_camera.getPosition() + glm::vec2(0, 0.5f));

			_fpsLimiter.end();
		}
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
		this->_gameWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_width, this->_height, flags);

		if (_gameWindow == nullptr)
			Error::fatal("Couldn't create the main window.");

		// Initializing opengl
		this->_glContext = SDL_GL_CreateContext(_gameWindow);
		if (this->_glContext == nullptr)
			Error::fatal("Couldn't create GL context");
		// Clearing input
		this->_input.clearInput();

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
		_spriteBatch.init();

		// Printing debug data
		std::cout << "CWD: " << Utility::getCwd() << std::endl;
		Utility::printOpenGLVersion();
	}

	void Window::initShaders()
	{
		_colorShader.compileShaders("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");
		_colorShader.addAttribute("vertPos");
		_colorShader.addAttribute("vertColor");
		_colorShader.addAttribute("vertUV");
		_colorShader.linkShaders();
	}

	int Window::getScreenHeight()
	{
		return this->_height;
	}

	int Window::getScreenWidth()
	{
		return this->_width;
	}
}