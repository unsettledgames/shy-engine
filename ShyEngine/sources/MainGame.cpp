#include <iostream>

#include <ShyEngine/Window.h>

using namespace ShyEngine;

int main(int argc, char** argv)
{
    Window engine(700, 400);

    engine.init("Test", 0 | WindowFlags::FULLSCREEN);
    engine.run();

    return 0;
}