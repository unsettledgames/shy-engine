// ShyEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>

#include <iostream>
#include <ShyEngine/Engine.h>

int main(int argc, char** argv)
{
    Engine engine(700, 400);
    engine.run();

    return 0;
}