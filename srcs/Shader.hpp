#ifndef SHADER_HPP
#define SHADER_HPP

#include "graphics.hpp"

class Shader{
	public:
		Shader(char* v, char* f);
		~Shader();
		unsigned int vert;
		unsigned int frag;
		unsigned int program;
	private:
};

#endif