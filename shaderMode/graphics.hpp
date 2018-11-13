#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif
#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

#define PI 3.14159265359
#define W 600
#define H 600

extern float camPos[3];
extern float camTar[3];
extern float angle;