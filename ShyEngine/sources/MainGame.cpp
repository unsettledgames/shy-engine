#include <iostream>

#include <ShyEngine.h>
#include <window/Window.h>


int main(int argc, char** argv)
{
    ShyEngine::Window engine(700, 400);
    
    engine.init("Test", SDL_WINDOW_OPENGL);
    engine.run();

    return 0;
}