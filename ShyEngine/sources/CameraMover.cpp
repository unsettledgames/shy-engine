#include <CameraMover.h>

void CameraMover::init() {}

void CameraMover::update()
{
	// TEST: W,A,S and D move the camera up, left, down, right
	if (SE::Input.getKeyDown(SDLK_w))
		SE::Engine.getCamera()->setPosition(SE::Engine.getCamera()->getPosition() + glm::vec2(0.0f, 6.0f) * SE::Engine.getDeltaTime());
	if (SE::Input.getKeyDown(SDLK_s))
		SE::Engine.getCamera()->setPosition(SE::Engine.getCamera()->getPosition() + glm::vec2(0.0f, -6.0f) * SE::Engine.getDeltaTime());
	if (SE::Input.getKeyDown(SDLK_a))
		SE::Engine.getCamera()->setPosition(SE::Engine.getCamera()->getPosition() + glm::vec2(-6.0f, 0.0f) * SE::Engine.getDeltaTime());
	if (SE::Input.getKeyDown(SDLK_d))
		SE::Engine.getCamera()->setPosition(SE::Engine.getCamera()->getPosition() + glm::vec2(6.0f, 0.0f) * SE::Engine.getDeltaTime());
}