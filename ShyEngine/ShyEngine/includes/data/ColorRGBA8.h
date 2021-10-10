#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

namespace ShyEngine
{
	class ColorRGBA8
	{
		private:
			// Color components
			GLubyte r;
			GLubyte g;
			GLubyte b;
			GLubyte a;
		public:
			ColorRGBA8() : r(0), g(0), b(0), a(0) {}

			ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
				r(R), g(G), b(B), a(A) {}

			/*
				\brief	Converts this ColorRGBA8 into an SDL_Color
			*/
			SDL_Color getSDLColor()
			{
				SDL_Color ret;

				ret.r = this->r;
				ret.g = this->g;
				ret.b = this->b;
				ret.a = this->a;

				return ret;
			}
	};
}
