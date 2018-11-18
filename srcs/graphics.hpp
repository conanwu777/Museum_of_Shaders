#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <string>
#include <iostream>
#include <OpenGL/gl3ext.h>
#endif
#include <GLFW/glfw3.h>

using namespace std;

struct Position {
	float x;
	float y;
};

#define W 1200
#define H 900
#define PI 3.14159265359

extern float g_light[3];

#endif