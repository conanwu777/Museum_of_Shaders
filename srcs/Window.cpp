#include "Window.hpp"

void	framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(){
	CreateWindow("", W, H);
	width = W;
	height = H;
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
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif	
	window = glfwCreateWindow(x, y, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
}

void	Window::Update(){
	glfwSwapBuffers(window);
	glfwPollEvents();  
}

void 	framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
} 