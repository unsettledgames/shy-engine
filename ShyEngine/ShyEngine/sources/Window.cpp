#include <Window.h>

namespace ShyEngine {
	Window::Window(int width, int height) :
		_width(width), _height(height), _time(0), _state(GameState::GAME_STATE_PAUSED), _gameWindow(nullptr),
		_fps(0), _maxFPS(60), _frameTime(0)
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

		// Running the engine loop until the user doesn't quit
		while (this->_state == GameState::GAME_STATE_RUNNING)
		{
			// Start and end times of the frame
			Uint32 startTicks = SDL_GetTicks();
			Uint32 frameTicks;
			// Processing input for this frame
			_input.processInput();
			
			// Setting up the shader
			_colorShader.use(_time);
			_colorShader.setOrthoProjection("orthoProj", _camera.getCameraMatrix());

			// Clearing buffers
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 1, 1);

			_spriteBatch.begin();
			Color col = { 255, 255, 255, 255 };
			GLuint tex = ResourcesManager::getTexture("textures/5heartsSmall.png").id;

			for (int i = 0; i < 10000; i++)
			{
				_spriteBatch.draw(glm::vec4(i, 0, 200, 200), glm::vec4(0, 0, 1, -1), 0, tex, col);
			}

			_spriteBatch.end();
			_spriteBatch.render();

			// Camera update
			_camera.update();

			// Cleanup
			SDL_GL_SwapWindow(this->_gameWindow);
			_colorShader.unuse();

			// If the user decided to quit, I stop the loop
			if (_input.isQuitting())
				this->_state = GameState::GAME_STATE_STOPPED;

			_time += 0.01f;

			// TEST
			if (_input.getKeyDown(SDLK_w))
				_camera.setPosition(_camera.getPosition() + glm::vec2(0, 0.5f));

			// Print FPS
			calculateFPS();
			if (frameCounter % 10 == 0)
				std::cout << "FPS: " << _fps << std::endl;
			frameCounter++;

			// Limit FPS
			/*frameTicks = SDL_GetTicks() - startTicks;
			if (1000.0f / _maxFPS > frameTicks)
				SDL_Delay(1000.0f / (_maxFPS - frameTicks));*/
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

		// Initializing the renderer
		this->_renderer.init(this->_gameWindow);
		// Clearing input
		this->_input.clearInput();

		// Initializing glew
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();

		if (err == GLEW_OK)
			std::cout << ("Initialized Glew") << std::endl;
		else
			Error::fatal("Couldn't initialize Glew");

		// IMPROVEMENT: let user decide v sync values, disabled atm
		SDL_GL_SetSwapInterval(0);
		// Initializing shaders
		initShaders();

		// TEST
		_spriteBatch.init();

		// Printing debug data
		std::cout << "CWD: " << Utility::getCwd() << std::endl;
		Utility::printOpenGLVersion();
	}

	void Window::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float prevTime = 0;
		static float sum = 0;
		static int timeIndex = 0;

		static Uint32 prevTicks = SDL_GetTicks();
		Uint32 currTicks = SDL_GetTicks();

		// Removing the last amount if I have more than NUM_SAMPLES frames
		if (timeIndex >= NUM_SAMPLES)
			sum -= prevTime;

		// Adding the new frame time
		_frameTime = currTicks - prevTicks;
		sum += _frameTime;
		prevTime = _frameTime;
		timeIndex++;

		// Computing FPS
		_fps = (1000.0f / (sum / NUM_SAMPLES));
		prevTicks = currTicks;
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