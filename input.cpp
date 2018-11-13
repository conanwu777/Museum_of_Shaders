#include "Input.hpp"
#include "math.h"

Input* Input::singleton;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (Input::singleton->cam.first){
        Input::singleton->cam.xMouse = xpos;
        // Input::singleton->cam.yMouse = ypos;
        Input::singleton->cam.first = false;
    }

    Input::singleton->cam.lookHoriz(xpos - Input::singleton->cam.xMouse);
    // Input::singleton->cam.lookVert(ypos - Input::singleton->cam.yMouse);
    Input::singleton->cam.xMouse = xpos;
    // Input::singleton->cam.yMouse = ypos;
}

Input::Input(Camera& c, Window& w) : cam(c), win(w){
    Input::singleton = this;
    glfwSetCursorPosCallback(win.window, &mouse_callback);
    startTime = glfwGetTime();
}

void Input::KeyHold(Window& win){
    curTime = glfwGetTime();
    if(glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win.window, true);
    if(glfwGetKey(win.window, GLFW_KEY_W) == GLFW_PRESS){
    	cam.pos[2] += cos(cam.getRotation()) * 0.03f;
    	cam.pos[0] -= sin(cam.getRotation()) * 0.03f;
        cam.reload();
    }
    if(glfwGetKey(win.window, GLFW_KEY_S) == GLFW_PRESS){
    	cam.pos[2] -= cos(cam.getRotation()) * 0.03f;
    	cam.pos[0] += sin(cam.getRotation()) * 0.03f;
        cam.reload();
    }
    if(glfwGetKey(win.window, GLFW_KEY_A) == GLFW_PRESS){
    	cam.pos[0] += cos(cam.getRotation()) * 0.03f;
    	cam.pos[2] += sin(cam.getRotation()) * 0.03f;
        cam.reload();
    }
    if(glfwGetKey(win.window, GLFW_KEY_D) == GLFW_PRESS){
    	cam.pos[0] -= cos(cam.getRotation()) * 0.03f;
    	cam.pos[2] -= sin(cam.getRotation()) * 0.03f;
        cam.reload();
    }
}