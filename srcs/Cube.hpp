#ifndef CUBE_HPP
#define CUBE_HPP
#include "RenderObject.hpp"

class Cube : public RenderObject{
    public:
        Cube(Shader& sha, Camera & c, float x, float y, float z,
        	float sX, float sY, float sZ, char *);
        virtual void    Activate(vector<RenderObject*> *vec);
        virtual void	SetCurrentRender();
        int				width, height, nrChannels;
        unsigned int	texture;
};

#endif
