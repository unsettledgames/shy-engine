#include <iostream>
#include <time.h>

#include <engine/ShyEngine.h>
#include <sstream>
#include <string>

/*
    CUSTOM SCRIPTS SYSTEM

    - User can create a class derived from UserProgram
    - User can derive from CollidableUserProgram if they want to have collisions
    - User can register a UserProgram and attach it to an entity
    - The engine updates all UserPrograms
*/

int main(int argc, char** argv)
{
    std::stringstream ballname;

    srand((unsigned)time(NULL));

    ShyEngine::ShyEngine engine(SDL_INIT_EVERYTHING);
    engine.createWindow(1000, 600, "Ballin", SDL_WINDOW_OPENGL);
    
    ShyEngine::Entity* ball;
    ShyEngine::ShaderProgram* shader = new ShyEngine::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");

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
            ball->getTransform()->setPos(glm::vec2(70 * i, 70 * j));

            ShyEngine::Sprite* ballSprite;
            // Adding the sprite
            if ((i + j) % 2 == 0)
            {
                ballSprite = new ShyEngine::Sprite(ball, "textures/AH.png",
                    shader, ShyEngine::ColorRGBA8(255, 255, 255, 255));
            }
            else
            {
                ballSprite = new ShyEngine::Sprite(ball, "textures/win.png",
                    shader, ShyEngine::ColorRGBA8(255, 255, 255, 255));
            }
             
            engine.registerModule<ShyEngine::Sprite>(ballSprite);
            ball->attachModule<ShyEngine::Sprite>(ballSprite);

            // Adding a circle collider
            ShyEngine::CircleCollider2D* circleCollider = new ShyEngine::CircleCollider2D(ball, 20);
            engine.registerModule<ShyEngine::CircleCollider2D>(circleCollider);
            ball->attachModule<ShyEngine::CircleCollider2D>(circleCollider);

            // Adding a physics module
            ShyEngine::Physics* physics = new ShyEngine::Physics(ball);
            engine.registerModule<ShyEngine::Physics>(physics);
            ball->attachModule<ShyEngine::Physics>(physics);

            // Adjusting physics
            physics->setMass(0.01f);
            physics->setVelocity( glm::vec2((((float)rand() / (RAND_MAX/2)) - 1) * 5.0f, (((float)rand() / RAND_MAX)) * 5.0f));
        }
    }

    ballname << "Ground";
    ball = engine.createEntity(ballname.str());

    // Adjusting the transform
    ball->getTransform()->setScale(glm::vec2(900, 100));
    ball->getTransform()->setPos(glm::vec2(350, -140));

    ShyEngine::Sprite* ballSprite;
        ballSprite = new ShyEngine::Sprite(ball, "textures/win.png",
            shader, ShyEngine::ColorRGBA8(255, 255, 255, 255));
    engine.registerModule<ShyEngine::Sprite>(ballSprite);
    ball->attachModule<ShyEngine::Sprite>(ballSprite);

    // Adding a circle collider
    ShyEngine::RectCollider2D* circleCollider = new ShyEngine::RectCollider2D(ball, glm::vec2(900, 100));
    engine.registerModule<ShyEngine::RectCollider2D>(circleCollider);
    ball->attachModule<ShyEngine::RectCollider2D>(circleCollider);

    // Adding a physics module
    ShyEngine::Physics* physics = new ShyEngine::Physics(ball);
    engine.registerModule<ShyEngine::Physics>(physics);
    ball->attachModule<ShyEngine::Physics>(physics);

    // Adjusting physics
    physics->setMass(0);

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