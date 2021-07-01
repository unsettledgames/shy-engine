#include <Engine.h>

Engine::Engine(int width, int height) : 
	_width(700), _height(400), _time(0), _state(GameState::GAME_STATE_PAUSED),_gameWindow(nullptr),
	_maxFPS(60)
{
}

Engine::~Engine()
{
}

void Engine::run()
{
	this->init();

	this->_state = GameState::GAME_STATE_RUNNING;

	this->loop();
}

void Engine::loop()
{
	static int frameCounter = 1;

	// Running the engine loop until the user doesn't quit
	while (this->_state == GameState::GAME_STATE_RUNNING)
	{
		// Start and end times of the frame
		float startTicks = SDL_GetTicks();
		float frameTicks;
		// Test sprite
		Sprite sprite(0, 0, 2, 2, "textures/5heartsSmall.png");
		// Processing input for this frame
		_input.processInput();
		// Rendering the sprite
		_colorShader.use(_time);		

		_renderer.render(sprite);
		_colorShader.unuse();

		// If the user decided to quit, I stop the loop
		if (_input.isQuitting())
		{
			this->_state = GameState::GAME_STATE_STOPPED;
		}

		_time += 0.01f;

		// Print FPS
		calculateFPS();
		if (frameCounter % 10 == 0)
			std::cout << "FPS: " << _fps << std::endl;
		frameCounter++;

		// Limit FPS
		frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
			SDL_Delay(1000.0f / (_maxFPS - frameTicks));
	}
}

void Engine::init()
{
	// Initializing SDL
	int sdlErr = SDL_Init(SDL_INIT_EVERYTHING);

	// Enabling double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Creating the game window
	this->_gameWindow = SDL_CreateWindow("Shy Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_width, this->_height, SDL_WINDOW_OPENGL);

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

	// Printing debug data
	std::cout << "CWD: " << Utility::getCwd() << std::endl;
	Utility::printOpenGLVersion();
}

void Engine::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float prevTime = 0;
	static float sum = 0;
	static int timeIndex = 0;

	static float prevTicks = SDL_GetTicks();
	float currTicks = SDL_GetTicks();
	int currNFrames;

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

void Engine::initShaders()
{
	_colorShader.compileShaders("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");
	_colorShader.addAttribute("vertPos");
	_colorShader.addAttribute("vertColor");
	_colorShader.addAttribute("vertUV");
	_colorShader.linkShaders();
}