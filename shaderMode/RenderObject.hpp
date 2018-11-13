#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include "graphics.hpp"
#include "Shader.hpp"
using namespace std;

class RenderObject{
    public:
        RenderObject(Shader& sha);
        RenderObject(Shader& sha, bool);
        ~RenderObject();
        void	Render();
        void	SetCurrentRender();
        void Update();
        unsigned int VBO;
        unsigned int VAO;
        void    Activate();
        unsigned int EBO;
        int numInd;
        int numVert;
    	Shader &shader;
    protected:
        float pos[3];
        float scale[3];
        float *verts;
    	unsigned int *indices;
};

#endif

