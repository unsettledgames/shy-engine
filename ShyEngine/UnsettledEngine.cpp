// UnsettledEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>

#include <iostream>
#include "headers/Test.h"
#include <Engine.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

int main(int argc, char** argv)
{
    Engine engine(700, 400);
    engine.run();

    return 0;
}