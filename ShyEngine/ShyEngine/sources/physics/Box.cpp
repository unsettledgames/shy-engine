#include <physics/Box.h>

namespace ShyEngine
{
	void Box::init(b2World* world, const glm::vec2& position, const glm::vec2& scale)
	{
		b2BodyDef bodyDef;
		b2PolygonShape boxShape;
		b2FixtureDef fixture;

		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);

		boxShape.SetAsBox(scale.x / 2, scale.y / 2);
		fixture.shape = &boxShape;
		fixture.density = 1.0f;
		fixture.friction = 0.3f;

		m_body = world->CreateBody(&bodyDef);
		m_fixture = m_body->CreateFixture(&fixture);
	}

	b2Body* Box::getBody()
	{
		return m_body;
	}

	b2Fixture* Box::getFixture()
	{
		return m_fixture;
	}
}