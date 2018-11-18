#include "stb_image.h"
#include "Panel.hpp"

Panel::Panel(Shader& sha, Camera& c, float x, float y, float z,
	float sX, float sY, float sZ, char *tex)
	: RenderObject(sha, c, x, y, z, sX, sY, sZ){
	verts = (float*)calloc(80, sizeof(float));
	indices = (unsigned int*)calloc(36, sizeof(int));

	numVert = 20;
	numInd = 6;

	verts[0] = 0.5f;
	verts[1] = 0.5f;
	verts[2] = 0.0f;
	verts[3] = 1.0f;
	verts[4] = 0.0f;

	verts[5] = .5f;
	verts[6] = -0.5f;
	verts[7] = 0.0f;
	verts[8] = 1.0f;
	verts[9] = 1.0f;

	verts[10] = -0.5f;
	verts[11] = -0.5f;
	verts[12] = 0.0f;
	verts[13] = 0.0f;
	verts[14] = 1.0f;

	verts[15] = -0.5f;
	verts[16] = 0.5f;
	verts[17] = 0.0f;
	verts[18] = 0.0f;
	verts[19] = 0.0f;


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	unsigned char *data = stbi_load(tex, &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void	Panel::SetCurrentRender(){
	glBindTexture(GL_TEXTURE_2D, texture);
	RenderObject::SetCurrentRender();
}
