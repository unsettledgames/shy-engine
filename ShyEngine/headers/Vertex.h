#pragma once

typedef struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Color;

typedef struct position
{
	float x;
	float y;
} Position;

struct Vertex
{
	Color color;
	Position position;
};