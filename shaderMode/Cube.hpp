#ifndef CUBE_HPP
#define CUBE_HPP

#include "RenderObject.hpp"
using namespace std;

class Cube : public RenderObject{
	public:
		Cube(Shader& sha, float x, float y, float z, float sX, float sY, float sZ);
		// ~Cube();
		// void	Render();
		// void	SetCurrentRender();
		// void Update();
};

#endif
