#include <Engine.h>

Engine::Engine(int width, int height) : 
	_width(700), _height(400), _time(0), _state(GameState::GAME_STATE_PAUSED),_gameWindow(nullptr)
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
	// Running the engine loop until the user doesn't quit
	while (this->_state == GameState::GAME_STATE_RUNNING)
	{
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
	}
}

void Engine::init()
{
	std::cout << "CWD: " << Utility::getCwd() << std::endl;
	// Initializing SDL
	int sdlErr = SDL_Init(SDL_INIT_EVERYTHING);

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

	// Enabling double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Initializing shaders
	initShaders();
}

void Engine::initShaders()
{
	_colorShader.compileShaders("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");
	_colorShader.addAttribute("vertPos");
	_colorShader.addAttribute("vertColor");
	_colorShader.addAttribute("vertUV");
	_colorShader.linkShaders();
}