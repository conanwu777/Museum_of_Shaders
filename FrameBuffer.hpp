#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "graphics.hpp"
#include "RenderObject.hpp"

using namespace std;

class FrameBuffer : public RenderObject{
    public:
    	FrameBuffer(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ);
    	~FrameBuffer();
		unsigned int fbo;
		void	Activate(vector<RenderObject*> *vec);
    private:
		unsigned int rbo;
};

#endif
