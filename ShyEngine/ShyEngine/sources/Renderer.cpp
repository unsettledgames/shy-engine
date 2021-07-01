#include <Renderer.h>

namespace ShyEngine {
	Renderer::Renderer()
	{
		this->_window = nullptr;
		this->_glContext = nullptr;
	}

	Renderer::~Renderer() {}

	void Renderer::init(SDL_Window* window)
	{
		this->_window = window;
		this->_glContext = SDL_GL_CreateContext(window);

		if (this->_glContext == nullptr)
			Error::fatal("Couldn't create GL context");
	}

	void Renderer::render(Sprite toRender)
	{
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);

		toRender.render();

		SDL_GL_SwapWindow(this->_window);
	}
}