#ifndef SHADERPANEL_HPP
#define SHADERPANEL_HPP

#include "RenderObject.hpp"
#include "Camera.hpp"

class ShaderPanel : public RenderObject{
	public:
	ShaderPanel(Shader& sha, Camera& c, float x, float y, float z, float sX, float sY, float sZ, vector<Position>& posArr);

	void	SetCurrentRender();
	void	Activate(vector<RenderObject*> *vec);
};

#endif
