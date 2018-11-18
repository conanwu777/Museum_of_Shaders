#ifndef POSTPROCESS_HPP
#define POSTPROCESS_HPP

#include "graphics.hpp"
#include "RenderObject.hpp"
#include "input.hpp"

class PostProcess : public RenderObject{
	public:
		unsigned int rbo;
		unsigned int fbo;
		unsigned int texture;
		
		PostProcess(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ);
		~PostProcess();
		bool on = false;
		void Enable();
		void	Activate(vector<RenderObject*> *vec);
		void	SetCurrentRender();
};

#endif