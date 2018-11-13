#include "Cube.hpp"

Cube::Cube(Shader& sha, float x, float y, float z, float sX, float sY, float sZ) : RenderObject(sha){
	verts = (float*)calloc(40, sizeof(float));
	indices = (unsigned int*)calloc(36, sizeof(int));

	numVert = 40;
	numInd = 36;
	float arrVert[] = {
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
	};

	int arrInd[] = {
		0,1,3,1,2,3,3,2,7,2,6,7,0,3,4,3,4,7,2,1,6,1,5,6,1,5,0,0,5,4,5,4,6,4,6,7
	};

	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	scale[0] = sX;
	scale[1] = sY;
	scale[2] = sZ;
	memcpy(verts, arrVert, 40 * sizeof(float));
	memcpy(indices, arrInd, 36 * sizeof(int));
}
