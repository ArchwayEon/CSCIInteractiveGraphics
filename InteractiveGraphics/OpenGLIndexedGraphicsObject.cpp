#include "OpenGLIndexedGraphicsObject.h"
#include "GLSLGraphicsShader.h"
#include "OpenGLVertexStrategy.h"

void OpenGLIndexedGraphicsObject::Setup()
{
   auto vertexStrategy = (OpenGLVertexStrategy*)this->vertexStrategy;
   vertexStrategy->CreateVAO();
   vertexStrategy->SelectVAO();
   vertexStrategy->CreateVBO();
   vertexStrategy->CreateIndexVBO();
   vertexStrategy->SetupBuffer();
   vertexStrategy->SetupIndexBuffer();
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

   auto vertexStrategy = (OpenGLVertexStrategy*)this->vertexStrategy;
   vertexStrategy->SelectVAO();
   vertexStrategy->SelectVBO();
   vertexStrategy->Render(GL_TRIANGLES);
   vertexStrategy->UnselectAll();
}
