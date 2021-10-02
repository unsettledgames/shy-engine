#pragma once

#include <glm/glm.hpp>

namespace ShyEngine
{
	class Box
	{
		private:
			b2Body* m_body;
			b2Fixture* m_fixture;
		public:
			void init(b2World* world, const glm::vec2& position, const glm::vec2& scale);

			b2Body* getBody();
			b2Fixture* getFixture();
	};
}