#include <iostream>

#include <engine/ShyEngine.h>


int main(int argc, char** argv)
{
    ShyEngine::ShyEngine engine(SDL_INIT_EVERYTHING);
    ShyEngine::Entity* test;

    engine.createWindow(700, 400, "Fancy test", SDL_WINDOW_OPENGL);
    
    test = engine.createEntity("Test entity");
    test->attachModule(ShyEngine::Sprite("textures/Alice.png", "shaders/defaultUnlit2D.vert", "shaders/defaultUnlit2D.frag"));

    engine.run();

    return 0;
}