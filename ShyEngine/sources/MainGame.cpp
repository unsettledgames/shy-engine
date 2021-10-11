#include <iostream>
#include <time.h>

#include <engine/ShyEngine.h>
#include <sstream>
#include <string>

namespace SE = ShyEngine;

/*
    TODO:

    - Update and register user programs
*/

int main(int argc, char** argv)
{
    /*
    std::stringstream bunnyName;
    srand((unsigned)time(NULL));

    SE::ShyEngine engine(SDL_INIT_EVERYTHING);
    engine.createWindow(1000, 600, "Bunnymark", SDL_WINDOW_OPENGL);

    SE::Entity* bunny;
    SE::ShaderProgram* shader = new SE::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");

    engine.registerShader(shader);*/

    std::stringstream ballname;

    srand((unsigned)time(NULL));

    // Create the engine
    SE::Engine = SE::_ShyEngine(SDL_INIT_EVERYTHING);
    SE::Engine.createWindow(1000, 600, "Ballin", SDL_WINDOW_OPENGL);

    // Engine settings
    SE::settings->collisions.addLayer("Walls");
    SE::settings->collisions.addLayer("Bunnies");
    // Bunnies don't collide with themselves
    SE::settings->collisions.defineCollision("Bunnies", "Bunnies", false);
    
    SE::Entity* ball;
    SE::ShaderProgram* shader = new SE::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");

    SE::Engine.registerShader(shader);
    
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            ballname << "Ballin " << i << ", " << j;
            ball = SE::Engine.createEntity(ballname.str());
            ball->setCollisionLayer("Bunnies");

            ballname.str("");
            ballname.clear();

            // Adjusting the transform
            ball->getTransform()->setScale(glm::vec2(40, 40));
            ball->getTransform()->setPos(glm::vec2(80 * i, 80 * j));

            SE::Sprite* ballSprite;
            // Adding the sprite
            if ((i + j) % 2 == 0)
            {
                ballSprite = new SE::Sprite(ball, "textures/AH.png",
                    shader, SE::ColorRGBA8(255, 255, 255, 255));
            }
            else
            {
                ballSprite = new SE::Sprite(ball, "textures/win.png",
                    shader, SE::ColorRGBA8(255, 255, 255, 255));
            }
             
            SE::Engine.registerModule<SE::Sprite>(ballSprite);
            ball->attachModule<SE::Sprite>(ballSprite);

            // Adding a physics module
            SE::Physics* physics = new SE::Physics(ball);
            SE::Engine.registerModule<SE::Physics>(physics);
            ball->attachModule<SE::Physics>(physics);

            // Adding a circle collider
            SE::CircleCollider2D* circleCollider = new SE::CircleCollider2D(ball, 20);
            SE::Engine.registerModule<SE::CircleCollider2D>(circleCollider);
            ball->attachModule<SE::CircleCollider2D>(circleCollider);
            
            // Adjusting physics
            physics->setMass(0.01f);
            physics->setVelocity( glm::vec2((((float)rand() / (RAND_MAX/2)) - 1) * 5.0f, (((float)rand() / RAND_MAX) * 5.0f)));
            physics->setBounciness(1.0f);
        }
    }

    ballname << "Ground";
    ball = SE::Engine.createEntity(ballname.str());

    // Adjusting the transform
    ball->getTransform()->setScale(glm::vec2(2700, 100));
    ball->getTransform()->setPos(glm::vec2(350, -140));

    SE::Sprite* ballSprite;
        ballSprite = new SE::Sprite(ball, "textures/win.png",
            shader, SE::ColorRGBA8(255, 255, 255, 255));
    SE::Engine.registerModule<SE::Sprite>(ballSprite);
    ball->attachModule<SE::Sprite>(ballSprite);

    SE::Physics* physics = new SE::Physics(ball);
    physics->setStatic(true);
    SE::Engine.registerModule<SE::Physics>(physics);
    ball->attachModule<SE::Physics>(physics);

    // Adding a rect collider
    SE::RectCollider2D* circleCollider = new SE::RectCollider2D(ball, glm::vec2(2700, 100));
    SE::Engine.registerModule<SE::RectCollider2D>(circleCollider);
    ball->attachModule<SE::RectCollider2D>(circleCollider);

    SE::Engine.run();

    return 0;
}