#include "ShaderPanel.hpp"
#include "input.hpp"
#include <math.h>

float g_light[3] = {0.5, 1.0, 0.0};

ShaderPanel::ShaderPanel(Shader& sha, Camera& c, float x, float y, float z, float sX, float sY, float sZ, vector<Position>& posArr): RenderObject(sha, c, 0, y, 0, sX, sY, sZ){
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

	Position tmp = {x, z};
	posArr.push_back(tmp);
}


void	ShaderPanel::SetCurrentRender(){
	RenderObject::SetCurrentRender();
	GLint uniZ = glGetUniformLocation(shader.program, "z");
	glUniform1f(uniZ, zOff);
	GLint uniX = glGetUniformLocation(shader.program, "x");
	glUniform1f(uniX, xOff);
	GLint uniTime = glGetUniformLocation(shader.program, "iTime");
	if (inside){
		glUniform1f(uniTime, inTime);
	}
	else{
		glUniform1f(uniTime, Input::singleton->startTime - Input::singleton->curTime);
	}
	GLint uniNear = glGetUniformLocation(shader.program, "far");
	glUniform1f(uniNear, !inside);
	float posArr[3];
	posArr[0] = - xOff - cam.pos[0];
	posArr[1] = 0;
	posArr[2] = zOff + cam.pos[2];

	float t2 = PI * 0.5 - atan2(posArr[2] , (posArr[0]));

	GLint uniPos = glGetUniformLocation(shader.program, "camPos");
	glUniform3fv(uniPos, 1, posArr);

	GLint uniXTheta = glGetUniformLocation(shader.program, "xAngle");
	glUniform1f(uniXTheta, cam.xRot - PI);

	GLint uniYTheta = glGetUniformLocation(shader.program, "yAngle");
	glUniform1f(uniYTheta, cam.yRot - PI);

	GLint uniInside = glGetUniformLocation(shader.program, "inside");
	glUniform1i(uniInside, inside);

	GLint uniLight = glGetUniformLocation(shader.program, "lightdir");
	glUniform3fv(uniLight, 1, g_light);
}

void    ShaderPanel::Activate(vector<RenderObject*> *vec){
	RenderObject::Activate(vec);
}
