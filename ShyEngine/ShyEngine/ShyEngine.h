#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

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
