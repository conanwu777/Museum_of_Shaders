#include "graphics.hpp"
#include "Shader.hpp"
#include "ShaderPanel.hpp"
#include "ShaderFrame.hpp"
#include "PostProcess.hpp"
#include "RenderObject.hpp"
#include "Cube.hpp"
#include "Panel.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include <vector>
#include <math.h>
#include <chrono>

bool    sortObjects(RenderObject* o1, RenderObject* o2)
{
	return o1->dist() > o2->dist();
}

int     main(){
	Window win("ShaderPixel", W ,H);

	glEnable(GL_BLEND);
	glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Camera cam;

	Shader bulbShader("shaders/billboardShader.vs", "shaders/mendelbulb.fs");
	Shader cubeShader("shaders/billboardShader.vs", "shaders/mendelbox.fs");
	Shader IFSShader("shaders/billboardShader.vs", "shaders/IFS.fs");
	Shader triangleShader("shaders/billboardShader.vs", "shaders/Sierpinski.fs");
	Shader sh("shaders/vertShader.vs", "shaders/regFrag.fs");
	Shader kleinianShader("shaders/frameVert.vs", "shaders/kleinian.fs");
	Shader galaxyShader("shaders/frameVert.vs", "shaders/galaxy.fs");
	Shader kalShader("shaders/frameVert.vs", "shaders/oct.fs");
	Shader glassShader("shaders/billboardShader.vs", "shaders/glassShader.fs");
	Shader cloudShader("shaders/billboardShader.vs", "shaders/cloudShader.fs");
	Shader uiShader("shaders/ui.vs", "shaders/regFrag.fs");
	Shader ppShader("shaders/ui.vs", "shaders/ppShader.fs");
	glEnable(GL_DEPTH_TEST);

	vector<RenderObject*> objs;
	vector<RenderObject*> uis;
	vector<RenderObject*> transparent;
	vector<RenderObject*> frames;
	vector<RenderObject*> fBuffs;
	vector<Position> blockPos;

	ShaderPanel bulb(bulbShader, cam, 2, 0, -1, 1, 1, 1, blockPos);
	ShaderPanel cube(cubeShader, cam, 0, 0, -1, 1, 1, 1, blockPos);
	ShaderPanel IFS(IFSShader, cam, 0, 0, 1, 1, 1, 1, blockPos);
	ShaderPanel tri(triangleShader, cam, -2, 0, 1, 1, 1, 1, blockPos);
	ShaderPanel glass(glassShader, cam, -2, 0, -1, 1, 1, 1, blockPos);
	ShaderPanel cloud(cloudShader, cam, 2, 0, 1, 1, 1, 1, blockPos);

	ShaderFrame fr(kleinianShader, cam,0, 1.4, 2.99, 2, 2, 2,false);
	ShaderFrame fr2(kalShader, cam,-3.99, 1.4, 0, 2, 2, 2,true);
	ShaderFrame fr3(galaxyShader, cam, 3.99, 1.4, 0, 2, 2, 2,true);
	Panel uiEnter(uiShader, cam, 0, -0.85, -1, 0.9, 0.09, 0.09, "texture/enter.png");
	Panel uiExit(uiShader, cam, 0, -0.85, -1, 0.9, 0.09, 0.09, "texture/exit.png");

	Cube floor(sh, cam, 0, -1.5, 0, 10, 1, 6, "texture/floor.png");
	Cube roof(sh, cam, 0, 4.5, 0, 10, 1, 6, "texture/roof.png");
	Cube wall1(sh, cam, 4.5, 1.5, 0, 1, 5, 6, "texture/wall.png");
	Cube wall2(sh, cam, -4.5, 1.5, 0, 1, 5, 6, "texture/wall.png");
	Cube wall3(sh, cam, 0, 1.5, 3.5, 10, 5, 1, "texture/wall.png");
	Cube wall4(sh, cam, 0, 1.5, -3.5, 10, 5, 1, "texture/wall.png");
	
	Cube pedestal(sh, cam, -2, -0.875, -1, 0.7, 0.25, 0.7, "texture/pedestal.png");
	Cube pedestal2(sh, cam, 0, -0.875, -1, 0.7, 0.25, 0.7, "texture/pedestal.png");
	Cube pedestal3(sh, cam, 2, -0.875, -1, 0.7, 0.25, 0.7, "texture/pedestal.png");
	Cube pedestal4(sh, cam, -2, -0.875, 1, 0.7, 0.25, 0.7, "texture/pedestal.png");
	Cube pedestal5(sh, cam, 0, -0.875, 1, 0.7, 0.25, 0.7, "texture/pedestal.png");
	Cube pedestal6(sh, cam, 2, -0.875, 1, 0.7, 0.25, 0.7, "texture/pedestal.png");
	
	Cube picFrame(sh, cam, 0, 1.4, 3.45, 2.3, 2.3, 1, "texture/frame.png");
	Cube picFrame2(sh, cam, 4.45, 1.4, 0, 1, 2.3, 2.3, "texture/frame.png");
	Cube picFrame3(sh, cam, -4.45, 1.4, 0, 1, 2.3, 2.3, "texture/frame.png");
	
	PostProcess postProc(ppShader, cam, 0, 0, 0, 1, 1, 1);

	Input   in(cam, win, uiEnter, uiExit, postProc);

	floor.Activate(&objs);
	wall1.Activate(&objs);
	wall2.Activate(&objs);
	wall3.Activate(&objs);
	wall4.Activate(&objs);
	roof.Activate(&objs);
	fr.Activate(&frames);
	fr2.Activate(&frames);
	fr3.Activate(&frames);
	pedestal.Activate(&objs);
	pedestal2.Activate(&objs);
	pedestal3.Activate(&objs);
	pedestal4.Activate(&objs);
	pedestal5.Activate(&objs);
	pedestal6.Activate(&objs);
	picFrame.Activate(&transparent);
	picFrame2.Activate(&transparent);
	picFrame3.Activate(&transparent);
	
	bulb.Activate(&transparent);
	cube.Activate(&transparent);
	IFS.Activate(&transparent);
	tri.Activate(&transparent);
	glass.Activate(&transparent);
	cloud.Activate(&transparent);
	uiEnter.Activate(&uis);
	uiExit.Activate(&uis);

	postProc.Activate(&uis);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	while(!glfwWindowShouldClose(win.window)){
		if (postProc.on){
			glBindFramebuffer(GL_FRAMEBUFFER, postProc.fbo);
		}
		else{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0859f, 0.121f, 0.226f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < objs.size(); i++)
		{
			objs[i]->SetCurrentRender();
			objs[i]->Render();
		}
		for (int i = 0; i < frames.size(); i++)
		{
			frames[i]->SetCurrentRender();
			frames[i]->Render();
		}
		sort(transparent.begin(), transparent.end(), sortObjects);
		for (int i = 0; i < transparent.size(); i++)
		{
			transparent[i]->SetCurrentRender();
			transparent[i]->Render();
		}

		if (postProc.on){
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			postProc.SetCurrentRender();
			postProc.Render();
		}
		in.KeyHold(win, transparent, frames);

		win.Update();
	}
}
