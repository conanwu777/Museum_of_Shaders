#include "ShaderPanel.hpp"
#include "Input.hpp"
#include <math.h>

ShaderPanel::ShaderPanel(Shader& sha, Camera& c, float x, float y, float z, float sX, float sY, float sZ): RenderObject(sha, c, 0, y, 0, sX, sY, sZ){
	verts = (float*)calloc(20, sizeof(float));
	indices = (unsigned int*)calloc(6, sizeof(int));

	xOff = x;
	zOff = z;

	numVert = 20;
	numInd = 6;

	verts[0] = 0.5f;
	verts[1] = 0.5f;
	verts[2] = 0.0f;
	verts[3] = 1.0f;
	verts[4] = 1.0f;

	verts[5] = .5f;
	verts[6] = -0.5f;
	verts[7] = 0.0f;
	verts[8] = 1.0f;
	verts[9] = 0.0f;

	verts[10] = -0.5f;
	verts[11] = -0.5f;
	verts[12] = 0.0f;
	verts[13] = 0.0f;
	verts[14] = 0.0f;

	verts[15] = -0.5f;
	verts[16] = 0.5f;
	verts[17] = 0.0f;
	verts[18] = 0.0f;
	verts[19] = 1.0f;


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;
}

void	ShaderPanel::SetCurrentRender(){
	RenderObject::SetCurrentRender();
	GLint uniZ = glGetUniformLocation(shader.program, "z");
    glUniform1f(uniZ, zOff);
    GLint uniX = glGetUniformLocation(shader.program, "x");
    glUniform1f(uniX, xOff);
    GLint uniTime = glGetUniformLocation(shader.program, "iTime");
    glUniform1f(uniTime, Input::singleton->startTime - Input::singleton->curTime);
    GLint uniNear = glGetUniformLocation(shader.program, "far");
    glUniform1f(uniNear, dist() > 0.5f);
    float posArr[3];
    posArr[0] = - xOff - cam.pos[0];
    posArr[1] = 0;
    posArr[2] = zOff + cam.pos[2];

    float t2 = 3.1416 * 0.5 - atan2(posArr[2] , (posArr[0]));

    // cout << "t2 : " << t2 << " view " << cam.xRot << endl;

    GLint uniPos = glGetUniformLocation(shader.program, "camPos");
    glUniform3fv(uniPos, 1, posArr);

    GLint uniXTheta = glGetUniformLocation(shader.program, "xAngle");
    glUniform1f(uniXTheta, cam.xRot - 3.1415);

    GLint uniYTheta = glGetUniformLocation(shader.program, "yAngle");
    glUniform1f(uniYTheta, cam.yRot - 3.1415);
}

void    ShaderPanel::Activate(vector<RenderObject*> *vec){
	RenderObject::Activate(vec);
}
