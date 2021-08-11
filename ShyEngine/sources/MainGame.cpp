#include <iostream>

#include <ShyEngine.h>


int main(int argc, char** argv)
{
    ShyEngine::ShyEngine engine(SDL_INIT_EVERYTHING);

    engine.createWindow(700, 400, "Fancy test", SDL_WINDOW_OPENGL);

    engine.run();

    return 0;
}