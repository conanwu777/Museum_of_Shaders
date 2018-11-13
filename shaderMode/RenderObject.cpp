#include "RenderObject.hpp"

RenderObject::RenderObject(Shader& sha) : shader(sha){
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	scale[0] = 1;
	scale[1] = 1;
	scale[2] = 1;
}

RenderObject::RenderObject(Shader& sha, bool test): shader(sha){
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	scale[0] = 1;
	scale[1] = 1;
	scale[2] = 1;

	verts = (float*)malloc(sizeof(float) * 20);
	indices = (unsigned int*)malloc(sizeof(int) * 6);
	numVert = 20;
	numInd = 6;
	verts[0] = 1.0f;
	verts[1] = 1.0f;
	verts[2] = 0.0f;
	verts[3] = 1.0f;
	verts[4] = 1.0f;

	verts[5] = 1.0f;
	verts[6] = -1.0f;
	verts[7] = 0.0f;
	verts[8] = 1.0f;
	verts[9] = 0.0f;

	verts[10] = -1.0f;
	verts[11] = -1.0f;
	verts[12] = 0.0f;
	verts[13] = 0.0f;
	verts[14] = 0.0f;

	verts[15] = -1.0f;
	verts[16] = 1.0f;
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

void	RenderObject::Activate(){

	for (int i = 0; i < numVert; i+=5){
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
}

RenderObject::~RenderObject(){
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	free(verts);
}

void	RenderObject::SetCurrentRender(){
	glUseProgram(shader.program);
}

void	RenderObject::Render(){
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numInd, GL_UNSIGNED_INT, 0);
}