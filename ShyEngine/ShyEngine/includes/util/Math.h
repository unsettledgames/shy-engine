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
	};
}