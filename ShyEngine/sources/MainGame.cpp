#include <iostream>

#include <engine/ShyEngine.h>
#include <string>

int main(int argc, char** argv)
{
    ShyEngine::ShyEngine engine(SDL_INIT_EVERYTHING);
    ShyEngine::Entity* test;

    ShyEngine::Transform* testTransform;
    ShyEngine::Sprite* testSprite;
    ShyEngine::Text* testText;

    ShyEngine::ShaderProgram shader;

    engine.createWindow(700, 400, "Fancy test", SDL_WINDOW_OPENGL);
    
    shader = ShyEngine::ShaderProgram("shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag");
    engine.registerShader(&shader);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            test = engine.createEntity("Test entity");

            testTransform = new ShyEngine::Transform(test, glm::vec2(100*i, 100*j), glm::vec2(200, 200));
            engine.registerModule(testTransform);
            test->attachModule(testTransform);

            testSprite = new ShyEngine::Sprite(test, "textures/Alice.png", shader);
            engine.registerModule(testSprite);
            test->attachModule(testSprite);
        }
    }

    test = engine.createEntity("TextEntity");

    testTransform = new ShyEngine::Transform(test, glm::vec2(20, 20));
    engine.registerModule(testTransform);
    test->attachModule(testTransform);

    testText = new ShyEngine::Text(test, "fonts/04.ttf", shader, 14, 1.0f, "abcdefghijklmnopqrstuvwxyz0123456789");
    engine.registerModule(testText);
    test->attachModule(testText);

    engine.run();

    return 0;
}