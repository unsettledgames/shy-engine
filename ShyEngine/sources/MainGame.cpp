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
    std::stringstream ballname;

    srand((unsigned)time(NULL));

    SE::ShyEngine engine(SDL_INIT_EVERYTHING);
    engine.createWindow(1000, 600, "Ballin", SDL_WINDOW_OPENGL);
    
    SE::Entity* ball;
    SE::ShaderProgram* shader = new SE::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");

    engine.registerShader(shader);
    
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            ballname << "Ballin " << i << ", " << j;
            ball = engine.createEntity(ballname.str());
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
             
            engine.registerModule<SE::Sprite>(ballSprite);
            ball->attachModule<SE::Sprite>(ballSprite);

            // Adding a physics module
            SE::Physics* physics = new SE::Physics(ball);
            engine.registerModule<SE::Physics>(physics);
            ball->attachModule<SE::Physics>(physics);

            // Adding a circle collider
            SE::CircleCollider2D* circleCollider = new SE::CircleCollider2D(ball, 20);
            engine.registerModule<SE::CircleCollider2D>(circleCollider);
            ball->attachModule<SE::CircleCollider2D>(circleCollider);
            
            // Adjusting physics
            physics->setMass(0.01f);
            physics->setVelocity( glm::vec2((((float)rand() / (RAND_MAX/2)) - 1) * 5.0f, (((float)rand() / RAND_MAX) * 5.0f)));
            physics->setBounciness(1.0f);
        }
    }

    ballname << "Ground";
    ball = engine.createEntity(ballname.str());

    // Adjusting the transform
    ball->getTransform()->setScale(glm::vec2(2700, 100));
    ball->getTransform()->setPos(glm::vec2(350, -140));

    SE::Sprite* ballSprite;
        ballSprite = new SE::Sprite(ball, "textures/win.png",
            shader, SE::ColorRGBA8(255, 255, 255, 255));
    engine.registerModule<SE::Sprite>(ballSprite);
    ball->attachModule<SE::Sprite>(ballSprite);

    SE::Physics* physics = new SE::Physics(ball);
    physics->setStatic(true);
    engine.registerModule<SE::Physics>(physics);
    ball->attachModule<SE::Physics>(physics);

    // Adding a rect collider
    SE::RectCollider2D* circleCollider = new SE::RectCollider2D(ball, glm::vec2(2700, 100));
    engine.registerModule<SE::RectCollider2D>(circleCollider);
    ball->attachModule<SE::RectCollider2D>(circleCollider);

    /*
    ShyEngine::ShyEngine engine(SDL_INIT_EVERYTHING);
    ShyEngine::Entity* test;

    ShyEngine::ParticleSystem* testParticleSystem;
    ShyEngine::Sprite* testSprite;
    ShyEngine::Text* testText;

    ShyEngine::ShaderProgram shader;

    engine.createWindow(1000, 600, "Fancy test", SDL_WINDOW_OPENGL);
    
    shader = ShyEngine::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");
    engine.registerShader(&shader);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            test = engine.createEntity("Test entity");
            test->getTransform()->setPos(glm::vec2(100 * i, 100 * j));
            test->getTransform()->setScale(glm::vec2(200, 200));

            testSprite = new ShyEngine::Sprite(test, "textures/Alice.png", &shader);
            engine.registerModule(testSprite);
            test->attachModule(testSprite);
        }
    }

    // Testing text
    test = engine.createEntity("TextEntity");
    test->getTransform()->setPos(glm::vec2(-500, -250));
    test->getTransform()->setScale(glm::vec2(1, 1));

    testText = new ShyEngine::Text(test, "fonts/04.ttf", &shader, ShyEngine::ColorRGBA8(255,255,255,255), 
        40, 1.0f, "abcdefghijklmnopqrstuvwxyz\n0123456789");
    engine.registerModule(testText);
    test->attachModule(testText);

    // Testing particle systems
    test = engine.createEntity("ParticleSystemEntity");
    test->getTransform()->setPos(glm::vec2(200, 200));
    test->getTransform()->setScale(glm::vec2(100, 100));

    testParticleSystem = new ShyEngine::ParticleSystem(test, 100, "textures/particle.png", &shader);
    engine.registerModule(testParticleSystem);
    test->attachModule(testParticleSystem);

    testParticleSystem->setEmissionRate(2);
    testParticleSystem->setLifetime(1000);
    */

    engine.run();

    return 0;
}