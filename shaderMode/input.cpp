#include "Input.hpp"
#include "math.h"

Input* Input::singleton;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    float theta = PI / 8 * (xpos * 2 / W - 1);
    float tau = -PI / 8 * (ypos * 2 / H - 1);
    camTar[0] = camPos[0] + 100 * sin(theta);
    camTar[1] = camPos[1] + 100 * sin(tau) * cos(theta);
    camTar[2] = camPos[2] - 100 * cos(tau) * cos(theta);
    angle = theta;
}

Input::Input(Window& w) : win(w){
    Input::singleton = this;
    glfwSetCursorPosCallback(win.window, &mouse_callback);
}

void Input::KeyHold(Window& win){
    if(glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win.window, true);
    if(glfwGetKey(win.window, GLFW_KEY_W) == GLFW_PRESS)
        camPos[2] -= 0.05;
    if(glfwGetKey(win.window, GLFW_KEY_S) == GLFW_PRESS)
        camPos[2] += 0.05;
    if(glfwGetKey(win.window, GLFW_KEY_A) == GLFW_PRESS)
        camPos[0] -= 0.05;
    if(glfwGetKey(win.window, GLFW_KEY_D) == GLFW_PRESS)
        camPos[0] += 0.05;
}
