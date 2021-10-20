#include <iostream>
#include <time.h>

#include <BunnyGenerator.h>
#include <CameraMover.h>

#include <engine/ShyEngine.h>
#include <sstream>
#include <string>

namespace SE = ShyEngine;

int main(int argc, char** argv)
{
    srand((unsigned)time(NULL));
    SE::Entity* bunny;
    SE::ShaderProgram* shader;
    BunnyGenerator* bunnyGenerator = new BunnyGenerator();
    CameraMover* cameraMover = new CameraMover();

    // Create the engine
    SE::Engine = SE::_ShyEngine(SDL_INIT_EVERYTHING);
    SE::Engine.createWindow(1000, 600, "Ballin", SDL_WINDOW_OPENGL, 120);

    shader = new SE::ShaderProgram("shaders/defaultUnlit2d.vert", "shaders/defaultUnlit2d.frag");

    // Engine settings
    SE::settings->collisions.addLayer("Walls");
    SE::settings->collisions.addLayer("Bunnies");
    // Bunnies don't collide with themselves
    SE::settings->collisions.defineCollision("Bunnies", "Bunnies", false);

    SE::Engine.registerModule<SE::UserScript>(bunnyGenerator);
    SE::Engine.registerModule<SE::UserScript>(cameraMover);

    // Create the ground
    bunny = SE::Engine.createEntity("Ground");

    // Adjusting the transform
    bunny->getTransform()->setScale(glm::vec2(2000, 100));
    bunny->getTransform()->setPos(glm::vec2(350, -140));

    SE::Sprite* ballSprite;
    ballSprite = new SE::Sprite(bunny, "textures/win.png",
        shader, SE::ColorRGBA8(255, 255, 255, 255));
    SE::Engine.registerModule<SE::Sprite>(ballSprite);
    bunny->attachModule<SE::Sprite>(ballSprite);

    SE::Physics* physics = new SE::Physics(bunny);
    physics->setStatic(true);
    SE::Engine.registerModule<SE::Physics>(physics);
    bunny->attachModule<SE::Physics>(physics);

    // Adding a rect collider
    SE::RectCollider2D* circleCollider = new SE::RectCollider2D(bunny, glm::vec2(2000, 100));
    SE::Engine.registerModule<SE::RectCollider2D>(circleCollider);
    bunny->attachModule<SE::RectCollider2D>(circleCollider);

    // WALLS
    // Create the ground
    bunny = SE::Engine.createEntity("Right");

    // Adjusting the transform
    bunny->getTransform()->setScale(glm::vec2(100, 1000));
    bunny->getTransform()->setPos(glm::vec2(900, 0));

    ballSprite = new SE::Sprite(bunny, "textures/win.png",
        shader, SE::ColorRGBA8(255, 255, 255, 255));
    SE::Engine.registerModule<SE::Sprite>(ballSprite);
    bunny->attachModule<SE::Sprite>(ballSprite);

    physics = new SE::Physics(bunny);
    physics->setStatic(true);
    SE::Engine.registerModule<SE::Physics>(physics);
    bunny->attachModule<SE::Physics>(physics);

    // Adding a rect collider
    circleCollider = new SE::RectCollider2D(bunny, glm::vec2(100, 1000));
    SE::Engine.registerModule<SE::RectCollider2D>(circleCollider);
    bunny->attachModule<SE::RectCollider2D>(circleCollider);

    // Create the ground
    bunny = SE::Engine.createEntity("Left");

    // Adjusting the transform
    bunny->getTransform()->setScale(glm::vec2(100, 1000));
    bunny->getTransform()->setPos(glm::vec2(-200, 100));

    ballSprite = new SE::Sprite(bunny, "textures/win.png",
        shader, SE::ColorRGBA8(255, 255, 255, 255));
    SE::Engine.registerModule<SE::Sprite>(ballSprite);
    bunny->attachModule<SE::Sprite>(ballSprite);

    physics = new SE::Physics(bunny);
    physics->setStatic(true);
    SE::Engine.registerModule<SE::Physics>(physics);
    bunny->attachModule<SE::Physics>(physics);

    // Adding a rect collider
    circleCollider = new SE::RectCollider2D(bunny, glm::vec2(100, 1000));
    SE::Engine.registerModule<SE::RectCollider2D>(circleCollider);
    bunny->attachModule<SE::RectCollider2D>(circleCollider);

    // Create the ground
    bunny = SE::Engine.createEntity("Top");

    // Adjusting the transform
    bunny->getTransform()->setScale(glm::vec2(2000, 100));
    bunny->getTransform()->setPos(glm::vec2(350, 600));

    ballSprite = new SE::Sprite(bunny, "textures/win.png",
        shader, SE::ColorRGBA8(255, 255, 255, 255));
    SE::Engine.registerModule<SE::Sprite>(ballSprite);
    bunny->attachModule<SE::Sprite>(ballSprite);

    physics = new SE::Physics(bunny);
    physics->setStatic(true);
    SE::Engine.registerModule<SE::Physics>(physics);
    bunny->attachModule<SE::Physics>(physics);

    // Adding a rect collider
    circleCollider = new SE::RectCollider2D(bunny, glm::vec2(2000, 100));
    SE::Engine.registerModule<SE::RectCollider2D>(circleCollider);
    bunny->attachModule<SE::RectCollider2D>(circleCollider);

    SE::Engine.run();

    return 0;
}