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
    	float xMouse;
    	float yMouse;
    	float first = false;
    	Camera();
		void	lookVert(float ammount);
		void	lookHoriz(float ammount);
		float	getRotation();
    	
    private:
    	void	reloadCameraAngle();
		float xRot;
    	float yRot;
    	const float FAR = 100;
    	const float NEAR = 0.01f;
    	const float FOV = 90;
};

#endif
