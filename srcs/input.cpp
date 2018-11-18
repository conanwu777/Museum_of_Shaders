#include "input.hpp"
#include "math.h"
#include "PostProcess.hpp"
#include <vector>

Input* Input::singleton;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	if (Input::singleton->cam.first){
		Input::singleton->cam.xMouse = xpos;
		Input::singleton->cam.yMouse = ypos;
		Input::singleton->cam.first = false;
	}

	Input::singleton->cam.lookHoriz(xpos - Input::singleton->cam.xMouse);
	Input::singleton->cam.lookVert(ypos - Input::singleton->cam.yMouse);
	Input::singleton->cam.xMouse = xpos;
	Input::singleton->cam.yMouse = ypos;
}

Input::Input(Camera& c, Window& w, Panel &uen, Panel &uex, PostProcess& p)
: cam(c), win(w), uiEnter(uen), uiExit(uex), pp(p)
{
	Input::singleton = this;
	glfwSetCursorPosCallback(win.window, &mouse_callback);
	startTime = glfwGetTime();
}

float   Input::dist(Position& a, Position& b){
	return (sqrt(pow(a.x + b.x, 2) + pow(a.y + b.y, 2)));
}

void Input::transparentCheck(Position& newCam, vector<RenderObject*> &panels){
	Position    tmp;
	Position    tmp2;
	

	for (int i = 0; i < panels.size(); i++){
		tmp.x = panels[i]->xOff;
		tmp.y = panels[i]->zOff;

		tmp2.x = cam.pos[0];
		tmp2.y = cam.pos[2];

		float d = dist(newCam, tmp);
		float d2 = dist(tmp2, tmp);

		if (d2 < 0.5 && d2 > 0.4 && spaceDown == false
			&& glfwGetKey(win.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			insideMode = !insideMode;
			if (insideMode)
				panels[i]->Enter();
			panels[i]->inside = !panels[i]->inside;
		}

		if (glfwGetKey(win.window, GLFW_KEY_Q) == GLFW_PRESS && panels[i]->inside){
			panels[i]->inTime -= 0.2;
		}

		if (glfwGetKey(win.window, GLFW_KEY_E) == GLFW_PRESS && panels[i]->inside){
			panels[i]->inTime += 0.2;
		}

		if (d < 0.5 && !insideMode){
			uiEnter.SetCurrentRender();
			uiEnter.Render();
		}
		if (d > 0.4 && panels[i]->inside){
			uiExit.SetCurrentRender();
			uiExit.Render();
		}

		if (d > 0.5 && panels[i]->inside){
			newCam.x = cam.pos[0];
			newCam.y = cam.pos[2];
			break;
		}
		if (d < 0.4 && !insideMode){
			newCam.x = cam.pos[0];
			newCam.y = cam.pos[2];
			break;
		}
	}
}

void Input::frameCheck(Position& newCam, Position& movCam, vector<RenderObject*> &panels){
	Position    tmp;

	for (int i = 0; i < panels.size(); i++){
		tmp.x = panels[i]->xOff;
		tmp.y = panels[i]->zOff;
		float d = dist(newCam, tmp);

		if (d < 0.8 && spaceDown == false && glfwGetKey(win.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			insideMode = !insideMode;
			if (insideMode)
				panels[i]->Enter();
			panels[i]->inside = !panels[i]->inside;
		}
		if (glfwGetKey(win.window, GLFW_KEY_Q) == GLFW_PRESS && panels[i]->inside)
			panels[i]->inTime -= 0.2;
		if (glfwGetKey(win.window, GLFW_KEY_E) == GLFW_PRESS && panels[i]->inside)
			panels[i]->inTime += 0.2;
		if (d < 0.8 && !insideMode){
			uiEnter.SetCurrentRender();
			uiEnter.Render();
		}
		if (d < 0.8 && panels[i]->inside){
			uiExit.SetCurrentRender();
			uiExit.Render();
		}
		if ( panels[i]->inside){
			panels[i]->inX += movCam.x;
			panels[i]->inZ += movCam.y;
			newCam.x = cam.pos[0];
			newCam.y = cam.pos[2];
			break;
		}

	}
}


void Input::KeyHold(Window& win, vector<RenderObject*> &panels, vector<RenderObject*> &frames){
	curTime = glfwGetTime();
	float deltaTime = curTime - lastTime;
	lastTime = glfwGetTime();

	if(glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win.window, true);
	Position newCam = {cam.pos[0],cam.pos[2]};
	Position movCam = {0,0};

	float moveSpeed = 0.03f;
	if (!insideMode){
		moveSpeed = deltaTime * 1.1f;
	}

	if(glfwGetKey(win.window, GLFW_KEY_W) == GLFW_PRESS){
		newCam.y += cos(cam.getRotation()) * moveSpeed;
		movCam.y += cos(cam.getRotation()) * 10 * moveSpeed;
		newCam.x -= sin(cam.getRotation()) * moveSpeed;
		movCam.x += -sin(cam.getRotation()) * 10 * moveSpeed;
	}
	if(glfwGetKey(win.window, GLFW_KEY_S) == GLFW_PRESS){
		newCam.y -= cos(cam.getRotation()) * moveSpeed;
		movCam.y += -cos(cam.getRotation()) * 10 * moveSpeed;
		newCam.x += sin(cam.getRotation()) * moveSpeed;
		movCam.x += sin(cam.getRotation()) * 10 * moveSpeed;
	}
	if(glfwGetKey(win.window, GLFW_KEY_A) == GLFW_PRESS){
		newCam.x += cos(cam.getRotation()) * moveSpeed;
		movCam.x += cos(cam.getRotation()) * 10 * moveSpeed;
		newCam.y += sin(cam.getRotation()) * moveSpeed;
		movCam.y += sin(cam.getRotation()) * 10 * moveSpeed;
	}
	if(glfwGetKey(win.window, GLFW_KEY_D) == GLFW_PRESS){
		newCam.x -= cos(cam.getRotation()) * moveSpeed;
		movCam.x += -cos(cam.getRotation()) * 10 * moveSpeed;
		newCam.y -= sin(cam.getRotation()) * moveSpeed;
		movCam.y += -sin(cam.getRotation()) * 10 * moveSpeed;
	}
	if(glfwGetKey(win.window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		spaceDown = false;
	if(glfwGetKey(win.window, GLFW_KEY_1) == GLFW_RELEASE)
		oneDown = false;
	transparentCheck(newCam, panels);
	frameCheck(newCam, movCam, frames);
	if (newCam.x != cam.pos[0] || newCam.y != cam.pos[2]){
		cam.pos[0] = newCam.x;
		cam.pos[2] = newCam.y;
		cam.reload();
	}
	if (glfwGetKey(win.window, GLFW_KEY_1) == GLFW_PRESS && oneDown == false)
		pp.on = !pp.on;
	if (glfwGetKey(win.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		spaceDown = true;
	if (glfwGetKey(win.window, GLFW_KEY_1) == GLFW_PRESS)
		oneDown = true;
	if (glfwGetKey(win.window, GLFW_KEY_LEFT) == GLFW_PRESS)
		g_light[0] -= (g_light[0] > -0.5 ? 0.02 : 0);
	if (glfwGetKey(win.window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		g_light[0] += (g_light[0] < 0.5 ? 0.02 : 0);
	if (glfwGetKey(win.window, GLFW_KEY_UP) == GLFW_PRESS)
		g_light[1] += (g_light[1] < 1 ? 0.02 : 0);
	if (glfwGetKey(win.window, GLFW_KEY_DOWN) == GLFW_PRESS)
		g_light[1] -= (g_light[1] > -1 ? 0.02 : 0);
	if (glfwGetKey(win.window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		g_light[2] += (g_light[2] < 0.5 ? 0.02 : 0);
	if (glfwGetKey(win.window, GLFW_KEY_MINUS) == GLFW_PRESS)
		g_light[2] -= (g_light[2] > -0.5 ? 0.02 : 0);
}