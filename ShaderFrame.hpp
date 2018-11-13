#ifndef SHADERFRAME_HPP
#define SHADERFRAME_HPP

#include "RenderObject.hpp"
#include "Input.hpp"
using namespace std;

class ShaderFrame : public RenderObject{
    public:
        ShaderFrame(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ, bool swap);
        void SetCurrentRender();
    private:
        bool swaped;
};

#endif
