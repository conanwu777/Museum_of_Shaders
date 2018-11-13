#ifndef SHADERPANEL_HPP
#define SHADERPANEL_HPP

#include "RenderObject.hpp"
#include "Camera.hpp"
using namespace std;

class ShaderPanel : public RenderObject{
    public:
        ShaderPanel(Shader& sha, Camera& c, float x, float y, float z, float sX, float sY, float sZ);
        // ~Cube();
        
        // void	Render();
        void	SetCurrentRender();
        void    Activate(vector<RenderObject*> *vec);
        // void Update();
        
};

#endif
