#include "stb_image.h"
#include "Cube.hpp"

Cube::Cube(Shader& sha, Camera& c, float x, float y, float z,
	float sX, float sY, float sZ, char *tex)
	: RenderObject(sha, c, x, y, z, sX, sY, sZ)
{
	verts = (float*)calloc(80, sizeof(float));
	indices = (unsigned int*)calloc(36, sizeof(int));

	numVert = 80;
	numInd = 36;

	float arrVert[] = {
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   sX, 0.0f,
		 0.5f,  0.5f,  0.5f,   sX,   sZ,
		-0.5f,  0.5f,  0.5f, 0.0f,   sZ,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f };

	int arrInd[] = {
		 8,  9, 11,  9, 10, 11,
		 3,  2,  7,  2,  6,  7,
		 0,  3,  4,  3,  4,  7,
		 2,  1,  6,  1,  5,  6,
		 1,  5,  0,  0,  5,  4,
		13, 12, 14, 14, 15, 12 };

	unsigned char *data = stbi_load(tex, &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	memcpy(verts, arrVert, numVert * sizeof(float));
	memcpy(indices, arrInd, numInd * sizeof(int));

	stbi_image_free(data);
}

void	Cube::Activate(vector<RenderObject*> *vec){
	RenderObject::Activate(vec);
}

void	Cube::SetCurrentRender(){
	glBindTexture(GL_TEXTURE_2D, texture);
	RenderObject::SetCurrentRender();
}
