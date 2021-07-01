#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Error.h>
#include <Sprite.h>

namespace ShyEngine {
	class Renderer
	{
	private:
		SDL_GLContext _glContext;
		SDL_Window* _window;
	public:
		Renderer();

		~Renderer();

		void init(SDL_Window* window);

		void render(Sprite toRender);
	};
}