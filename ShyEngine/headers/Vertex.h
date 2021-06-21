// OPTIMIZABLE: make colour and position independent typedefs, move to something like GenericStructs.h
#pragma once

struct Vertex
{
	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} color;

	struct Position
	{
		float x;
		float y;
	} position;
};