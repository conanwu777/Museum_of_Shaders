#ifndef INPUT_HPP
#define INPUT_HPP

#include "Camera.hpp"
#include "Window.hpp"
#include "graphics.hpp"
using namespace std;

class Input{
    public:
    	float curTime;
    	float startTime;
    	
    	Input(Camera& c, Window& w);
    	Camera& cam;
    	Window& win;
        void KeyHold(Window& win);
        static Input* singleton;
    private:

};

#endif