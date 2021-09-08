#include <iostream>
#include <time.h>

#include <engine/ShyEngine.h>
#include <string>

int main(int argc, char** argv)
{
    srand((unsigned)time(NULL));

    ShyEngine::ShyEngine engine(SDL_INIT_EVERYTHING);
    engine.createWindow(1000, 600, "Ballin", SDL_WINDOW_OPENGL);
    
    ShyEngine::Entity* ball;
    ShyEngine::ShaderProgram* shader = new ShyEngine::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");

    engine.registerShader(shader);

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            ball = engine.createEntity("Ballin");

            // Adjusting the transform
            ball->getTransform()->setScale(glm::vec2(20, 20));
            ball->getTransform()->setPos(glm::vec2(25 * i, 25 * j));

            // Adding the sprite
            ShyEngine::Sprite* ballSprite = new ShyEngine::Sprite(ball, "textures/AH.png",
                shader, ShyEngine::ColorRGBA8(255, 255, 255, 255));
            engine.registerModule(ballSprite);
            ball->attachModule(ballSprite);

            // Adding a circle collider
            /*
            ShyEngine::CircleCollider2D* circleCollider = new ShyEngine::CircleCollider2D(ball, 100);
            engine.registerModule(circleCollider);
            ball->attachModule(circleCollider);*/

            // Adding a physics module
            ShyEngine::Physics* physics = new ShyEngine::Physics(ball);
            engine.registerModule(physics);
            ball->attachModule(physics);

            // Adjusting physics
            physics->setMass(0.02f);
            physics->setVelocity(glm::vec2((((float)rand() / (RAND_MAX/2)) - 1) * 10.0f, (((float)rand() / RAND_MAX)) * 10.0f));
        }
    }

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