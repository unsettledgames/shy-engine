#include <BunnyGenerator.h>
#include <sstream>

namespace SE = ShyEngine;

void BunnyGenerator::init()
{
	SE::Entity* textEntity = SE::Engine.createEntity("FPS");
	textEntity->getTransform()->setPos(glm::vec2(-200, 400));

	// Generate shaders
	m_shader = new SE::ShaderProgram("shaders/defaultUnlit2d.vert", "shaders/defaultUnlit2d.frag");

	// Add fps text
	m_fpsCounter = new SE::Text(textEntity, "fonts/04.TTF", m_shader, SE::ColorRGBA8(255, 255, 255, 255), 20, 0, "sas");
	textEntity->attachModule<SE::Text>(m_fpsCounter);
	SE::Engine.registerModule<SE::Text>(m_fpsCounter);
}

void BunnyGenerator::update()
{
	std::stringstream fpsText;

	if (SE::Input.getKeyDown(SDLK_b))
		generateBunny();

	fpsText << "Bunnies: " << m_currBunnies << ", FPS: " << SE::Engine.getFPS();

	m_fpsCounter->setText(fpsText.str());
}

void BunnyGenerator::generateBunny()
{
	/*if (!m_canGenerate)
		return;*/
	m_canGenerate = false;
	// Create an entity
	SE::Entity* bunny = SE::Engine.createEntity("Bunny");
	bunny->setCollisionLayer("Bunnies");
	// Offset the bunny
	bunny->getTransform()->setPos(glm::vec2(0, 200) + glm::vec2(rand() % 50, rand() % 50));
	bunny->getTransform()->setScale(glm::vec2(50, 50));

	// Add a sprite with a random color
	SE::Sprite* sprite = new SE::Sprite(bunny, "textures/Bunny.png", m_shader, 
		SE::ColorRGBA8(rand() % 255, rand() % 255, rand() % 255, 255));

	// Add a physics module
	SE::Physics* physics = new SE::Physics(bunny);
	physics->setMass(0.02f);
	physics->setVelocity(glm::vec2(-5 + rand() % 10,  rand() % 5));

	// Add a collider module
	SE::CircleCollider2D* coll = new SE::CircleCollider2D(bunny, 25);

	// Register modules
	SE::Engine.registerModule<SE::Sprite>(sprite);
	SE::Engine.registerModule<SE::Physics>(physics);
	SE::Engine.registerModule<SE::CircleCollider2D>(coll);

	// Attach modules
	bunny->attachModule<SE::Sprite>(sprite);
	bunny->attachModule<SE::Physics>(physics);
	bunny->attachModule<SE::CircleCollider2D>(coll);

	nextBunnyTime += 500;
}