#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ) : RenderObject(sha, c, 0, y, 0, sX, sY, sZ){
	verts = (float*)calloc(40, sizeof(float));
	indices = (unsigned int*)calloc(36, sizeof(int));

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

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		cout << "FrameBuffer NOT complete!\n";
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

FrameBuffer::~FrameBuffer(){
	glDeleteFramebuffers(1, &fbo);
}

void    FrameBuffer::Activate(vector<RenderObject*> *vec){
	RenderObject::Activate(vec);
	vec->push_back(this);
}