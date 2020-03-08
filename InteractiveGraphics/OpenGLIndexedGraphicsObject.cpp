#include "OpenGLIndexedGraphicsObject.h"
#include "GLSLGraphicsShader.h"

void OpenGLIndexedGraphicsObject::Setup()
{
   glGenVertexArrays(1, &_vaoId);
   glBindVertexArray(_vaoId);
   glGenBuffers(1, &_vboId);
   glGenBuffers(1, &_indexVbo);
   this->vertexStrategy->SetupBuffer(_vboId);
   this->vertexStrategy->SetupIndexBuffer(_indexVbo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

void OpenGLIndexedGraphicsObject::Render()
{
   auto shader = (GLSLGraphicsShader*)_shader;
   shader->Select();

   shader->SendMatricesToGPU();
   shader->SendMatrixToGPU("world", frame.orientation);

   glBindVertexArray(_vaoId);
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);

   this->vertexStrategy->RenderWithIndex(_indexVbo, GL_TRIANGLES);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}
