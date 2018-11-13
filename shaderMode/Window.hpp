#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "graphics.hpp"
using namespace std;

class Window{
    public:
        Window();
        ~Window();
        Window(string name, int x, int y);
        void Update();
        GLFWwindow* window;
    private:
        void    CreateWindow(string name, int x, int y);
};

#endif