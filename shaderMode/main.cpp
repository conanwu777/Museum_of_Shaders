#include "graphics.hpp"
#include "Shader.hpp"
#include "RenderObject.hpp"
#include "Cube.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include <vector>
#include <chrono>

float camPos[3] = {0, 0, 1.5};
float camTar[3] = {0, 0, -100};
float angle = 0;

int     main(){
	Window win("ShaderPixel", 1200 ,1200);
    glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	Input   in(win);
	float curTime; //timerClass ??
	float startTime = glfwGetTime();
	Shader sh("vertShader.vs", "cloud.fs");
	vector<RenderObject*> objs;
	RenderObject obj(sh,0);
	obj.Activate();
	objs.push_back(&obj);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	GLint uniTime = glGetUniformLocation(sh.program, "iTime");
	while(!glfwWindowShouldClose(win.window)){
		GLint unCampos = glGetUniformLocation(sh.program, "camPos");
		GLint unAngle = glGetUniformLocation(sh.program, "angle");
		curTime = glfwGetTime();
		in.KeyHold(win);
		glClearColor(0.0859f, 0.121f, 0.226f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < objs.size(); i++){
			
			objs[i]->SetCurrentRender();
			glUniform1f(uniTime, curTime - startTime);
			glUniform3fv(unCampos, 1, camPos);
			glUniform1f(unAngle, angle);
			objs[i]->Render();
		}
		win.Update();
	}
}