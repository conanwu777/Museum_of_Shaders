#include "PostProcess.hpp"

PostProcess::PostProcess(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ) : RenderObject(sha, c, 0, y, 0, sX, sY, sZ)
{
	verts = (float*)calloc(20, sizeof(float));
	indices = (unsigned int*)calloc(6, sizeof(int));

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

	
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W* 2, H * 2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, W * 2, H * 2);  
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		cout << "FrameBuffer NOT complete!\n";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void    PostProcess::Activate(vector<RenderObject*> *vec){
	RenderObject::Activate(vec);
	vec->push_back(this);
}

void	PostProcess::SetCurrentRender(){	
	glBindTexture(GL_TEXTURE_2D, texture);
	RenderObject::SetCurrentRender();
}

PostProcess::~PostProcess(){
	glDeleteFramebuffers(1, &fbo);
}

void	PostProcess::Enable(){
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}