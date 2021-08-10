#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <rendering/SpriteBatch.h>
#include <window/Window.h>

namespace ShyEngine {
	class ShyEngine
	{
	private:

		void init();

	public:
		ShyEngine();

		~ShyEngine();
	};
}
