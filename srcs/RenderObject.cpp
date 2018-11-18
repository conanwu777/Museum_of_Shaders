#include "RenderObject.hpp"
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "input.hpp"

RenderObject::RenderObject(Shader& sha, Camera& c, float x, float y, float z, float sX, float sY, float sZ) : shader(sha), cam(c){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	scale[0] = sX;
	scale[1] = sY;
	scale[2] = sZ;
	xOff = x;
	zOff = z;
}

void	RenderObject::Activate(vector<RenderObject*> *vec)
{
	for (int i = 0; i < numVert; i += 5)
	{
		verts[i] *= scale[0];
		verts[i] += pos[0];
		verts[i + 1] *= scale[1];
		verts[i + 1] += pos[1];
		verts[i + 2] *= scale[2];
		verts[i + 2] += pos[2];
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVert, verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numInd, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	vec->insert(vec->begin(), this);	
}

RenderObject::~RenderObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	free(verts);
	free(indices);
}

void	RenderObject::Enter()
{
	inTime = Input::singleton->startTime - Input::singleton->curTime;
}

float	RenderObject::dist()
{
	return (sqrt(pow(xOff + cam.viewMat[12], 2) + pow(zOff + cam.viewMat[14], 2)));
}

void	RenderObject::SetCurrentRender()
{
	glUseProgram(shader.program);

	GLint uniProj = glGetUniformLocation(shader.program, "projection");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, cam.projectionMat);
	GLint uniYaw = glGetUniformLocation(shader.program, "yaw");
	glUniformMatrix4fv(uniYaw, 1, GL_FALSE, cam.yawMat);
	GLint uniPitch = glGetUniformLocation(shader.program, "pitch");
	glUniformMatrix4fv(uniPitch, 1, GL_FALSE, cam.pitchMat);
	GLint uniView = glGetUniformLocation(shader.program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, cam.viewMat);
}

void	RenderObject::Render()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numInd, GL_UNSIGNED_INT, 0);
}
