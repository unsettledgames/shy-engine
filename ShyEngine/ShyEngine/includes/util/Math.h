#pragma once

#include <glm/glm.hpp>

namespace ShyEngine
{
	class Math
	{
		public:	
			static glm::vec2 rotatePoint(glm::vec2 point, float angle)
			{
				return glm::vec2(point.x * cos(angle) - point.y * sin(angle),
					point.x * sin(angle) + point.y * cos(angle));
			}

			static int closestPow2(int i)
			{
				i--;
				int pi = 1;
				while (i > 0) {
					i >>= 1;
					pi <<= 1;
				}
				return pi;
			}
	};
}