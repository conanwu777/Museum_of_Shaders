#ifndef BUFFERCUBE_HPP
#define BUFFERCUBE_HPP

#include "Cube.hpp"
using namespace std;

struct ssbo_data
{
    float test[100];
};

class BufferCube : public Cube{
    public:
        BufferCube(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ,char *);
        void Activate(vector<RenderObject*> *vec);
        void	SetCurrentRender();
        GLuint abo;
};

#endif
