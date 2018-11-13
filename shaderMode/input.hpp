#ifndef INPUT_HPP
#define INPUT_HPP

#include "Camera.hpp"
#include "Window.hpp"
#include "graphics.hpp"
using namespace std;

class Input{
	public:
		Input(Window& w);
		Window& win;
		void KeyHold(Window& win);
		static Input* singleton;
};

#endif