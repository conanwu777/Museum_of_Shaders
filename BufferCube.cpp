#include "BufferCube.hpp"
#include <stdlib.h>

BufferCube::BufferCube(Shader& sha, Camera & c, float x, float y, float z, float sX, float sY, float sZ,char *t) : Cube(sha, c, x, y, z, sX, sY, sZ, t){

}


void   BufferCube::Activate(vector<RenderObject*> *vec){
  Cube::Activate(vec);
  glGenBuffers(1, &abo);
  glBindBuffer(GL_ARRAY_BUFFER, abo);
  glBufferData(GL_ARRAY_BUFFER, 1000 * sizeof(float), NULL, GL_STATIC_COPY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferCube::SetCurrentRender(){
  RenderObject::SetCurrentRender();
  glBindBuffer(GL_ARRAY_BUFFER, abo);

  float arr[1000];
  for (int i = 0; i < 1000; i++){
    arr[i] = rand() / (float)RAND_MAX;
  }

  glBufferSubData(GL_ARRAY_BUFFER, 0, 1000 * sizeof(float), arr);
  // GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
  // memcpy(p, &shader_data, sizeof(shader_data))
  // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}
