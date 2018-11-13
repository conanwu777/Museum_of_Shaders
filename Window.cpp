#include "Window.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(){
	CreateWindow("", 800, 600);
	width = 800;
	height = 600;
}

Window::~Window(){
	glfwTerminate();
}

Window::Window(string name, int x, int y){
	CreateWindow(name, x, y);
	width = x;
	height = y;
}

void	Window::CreateWindow(string name, int x, int y)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
    	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif	
	window = glfwCreateWindow(x, y, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
//rezise
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
}

void Window::Update(){
	glfwSwapBuffers(window);
	glfwPollEvents();  
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
} 