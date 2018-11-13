#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "graphics.hpp"
using namespace std;

class Camera{
    public:
    	float *projectionMat;
    	float *yawMat;
    	float *pitchMat;
    	float *viewMat;
        float pos[3];
    	float xMouse;
    	float yMouse;
    	float first = false;
    	Camera();
		void	lookVert(float ammount);
		void	lookHoriz(float ammount);
		float	getRotation();
        void    reload();
        float xRot;
        float yRot;
    	
    private:
    	void	reloadCameraAngle();
    	const float FAR = 100;
    	const float PI = 3.1415;
    	const float NEAR = 0.01f;
    	const float FOV = 90;
};

#endif