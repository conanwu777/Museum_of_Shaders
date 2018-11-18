#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include "graphics.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include <vector>

class RenderObject
{
	public:
		RenderObject(Shader& sha, Camera& c, float x, float y, float z,
			float sX, float sY, float sZ);
		~RenderObject();
		void	Render();
		virtual void	SetCurrentRender();
		void	Update();
		unsigned int	VBO;
		unsigned int	VAO;
		unsigned int	EBO;
		virtual void	Activate(vector<RenderObject*> *vec);
		float	dist();
		void	Enter();
		float	inTime;
		int		numInd;
		int		numVert;
		Shader	&shader;
		Camera	&cam;
		float	xOff;
		bool	inside = false;
		float	zOff;
		float	inX, inZ;
	protected:
		float	pos[3];
		float	scale[3];
		float	*verts;
		unsigned int	*indices;
};

#endif

