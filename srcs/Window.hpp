#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "graphics.hpp"

class Window{
	public:
		Window();
		~Window();
		Window(string name, int x, int y);
		void	Update();
		GLFWwindow* window;
		int		width, height;
	private:
		void	CreateWindow(string name, int x, int y);
};

#endif