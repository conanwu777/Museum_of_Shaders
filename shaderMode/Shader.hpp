#ifndef SHADER_HPP
#define SHADER_HPP

#include "graphics.hpp"
using namespace std;

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