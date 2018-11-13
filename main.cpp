#include "graphics.hpp"
#include "Shader.hpp"
#include "ShaderPanel.hpp"
#include "ShaderFrame.hpp"
#include "RenderObject.hpp"
#include "Cube.hpp"
#include "FrameBuffer.hpp"
#include "BufferCube.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include <vector>
#include <math.h>
#include <chrono>

bool    sortObjects(RenderObject* o1, RenderObject* o2){
    return o1->dist() > o2->dist();
}

int     main(){
    Window win("ShaderPixel", 1028 ,720);

    glEnable(GL_BLEND);
    glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Camera cam;
    Input   in(cam, win);

    Shader bulbShader("billboardShader.vs", "mendelbulb.fs");
    Shader cubeShader("billboardShader.vs", "mendelbox.fs");
    Shader IFSShader("billboardShader.vs", "IFS.fs");
    Shader triangleShader("billboardShader.vs", "triangle.fs");
    Shader sh("vertShader.vs", "regFrag.fs");
    Shader kleinianShader("vertShader.vs", "kleinian.fs");
    Shader glassShader("billboardShader.vs", "glassShader.fs");
    glEnable(GL_DEPTH_TEST);

    vector<RenderObject*> objs;
    vector<RenderObject*> transparent;
    vector<RenderObject*> fBuffs;

    ShaderPanel tr(bulbShader, cam, -1.5, 0, -2,1.5,1.5,1.5);
    ShaderPanel tr2(cubeShader, cam, 0, 0, -2,1.5,1.5,1.5);
    ShaderPanel tr3(IFSShader, cam, 1.5, 0, -2,1.5,1.5,1.5);
    ShaderPanel tr4(triangleShader, cam, 3, 0, -2,1.5,1.5,1.5);
    ShaderPanel tr5(glassShader, cam, -3, 0, -2,1.5,1.5,1.5);

    ShaderFrame fr(kleinianShader, cam,4.49, 1.2 , -2,2,2,2, true);

    BufferCube bCube(sh, cam, 0, -1, -2, 10,1,6, "");

    Cube obj(sh, cam, 0, -1.5, -2, 10,1,6, "floor.png");
    Cube roof(sh, cam, 0, 4.5, -2, 10,1,6, "roof.png");
    Cube obj2(sh, cam, 5, 1.5, -2, 1,5,6, "wall.png");
    Cube obj3(sh, cam, -5, 1.5, -2, 1,5,6, "wall.png");
    Cube obj4(sh, cam, 0, 1.5, 1, 10,5,1, "wall.png");
    Cube obj5(sh, cam, 0, 1.5, -5, 10,5,1, "wall.png");
    FrameBuffer fb(sh, cam, -2, 1.5, 0, 1,1,1);


    obj.Activate(&objs);
    obj2.Activate(&objs);
    obj3.Activate(&objs);
    obj4.Activate(&objs);
    obj5.Activate(&objs);
    roof.Activate(&objs);

    fr.Activate(&objs);
    // bCube.Activate(&objs);
    tr.Activate(&transparent);
    tr2.Activate(&transparent);
    tr3.Activate(&transparent);
    tr4.Activate(&transparent);
    tr5.Activate(&transparent);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(win.window)){
        in.KeyHold(win);

        // glBindFramebuffer(GL_FRAMEBUFFER, fb.fbo);
        glClearColor(0.0859f, 0.121f, 0.226f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < objs.size(); i++){
            objs[i]->SetCurrentRender();
            objs[i]->Render();
        }
        sort(transparent.begin(), transparent.end(), sortObjects);
        for (int i = 0; i < transparent.size(); i++){
            transparent[i]->SetCurrentRender();
            transparent[i]->Render();
        }

        win.Update();
    }
}
