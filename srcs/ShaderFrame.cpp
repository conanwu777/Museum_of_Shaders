#include "ShaderFrame.hpp"
#include "input.hpp"

ShaderFrame::ShaderFrame(Shader& sha, Camera & c, float x, float y, float z,
	float sX, float sY, float sZ, bool swap)
	: RenderObject(sha, c, x, y, z, sX, sY, sZ)
{
	verts = (float*)calloc(20, sizeof(float));
	indices = (unsigned int*)calloc(6, sizeof(int));

	swaped = swap;
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

	if (swap)
	{
		for (int i = 0; i < numVert/5; i++)
		{
			verts[i * 5 + 2] = verts[i * 5];
			verts[i * 5] = 0;
		}
	}
}

void ShaderFrame::SetCurrentRender()
{
	RenderObject::SetCurrentRender();
	GLint uniTime = glGetUniformLocation(shader.program, "iTime");
	if (inside)
		glUniform1f(uniTime, inTime);
	else
	  glUniform1f(uniTime, Input::singleton->startTime - Input::singleton->curTime);
	GLint uniNear = glGetUniformLocation(shader.program, "far");
	glUniform1f(uniNear, !inside);

	float posArr[3];
	posArr[0] = -xOff - inX - cam.pos[0];
	posArr[1] = 0;
	posArr[2] = zOff - inZ + cam.pos[2];
	if (swaped)
	{
		float tmp = posArr[0];
		posArr[0] = posArr[2];
		posArr[2] = tmp;
	}
	GLint uniPos = glGetUniformLocation(shader.program, "camPos");
	glUniform3fv(uniPos, 1, posArr);
	GLint uniXTheta = glGetUniformLocation(shader.program, "xAngle");
	glUniform1f(uniXTheta, cam.xRot - PI);
	GLint uniYTheta = glGetUniformLocation(shader.program, "yAngle");
	glUniform1f(uniYTheta, cam.yRot - PI);
	GLint uniInside = glGetUniformLocation(shader.program, "inside");
	glUniform1i(uniInside, inside);
	GLint uniSwap = glGetUniformLocation(shader.program, "swap");
	glUniform1i(uniSwap, swaped);
}
