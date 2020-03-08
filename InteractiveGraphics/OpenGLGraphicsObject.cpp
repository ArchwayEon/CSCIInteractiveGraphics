#include "OpenGLGraphicsObject.h"
#include "GLSLGraphicsShader.h"
#include <glm/gtc/matrix_transform.hpp>

OpenGLGraphicsObject::~OpenGLGraphicsObject()
{
   glDeleteVertexArrays(1, &_vaoId);
}

void OpenGLGraphicsObject::Setup()
{
   glGenVertexArrays(1, &_vaoId);
   glBindVertexArray(_vaoId);
   // Declare the buffer object and store a handle to the object
   glGenBuffers(1, &_vboId);
   this->vertexStrategy->SetupBuffer(_vboId);
   if (_texture != nullptr) {
      _texture->Setup();
   }
   // Good practice to cleanup by unbinding 
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

void OpenGLGraphicsObject::Render()
{
   auto shader = (GLSLGraphicsShader*)_shader;
   shader->Select();
   shader->SendMatricesToGPU();
   shader->SendMatrixToGPU("world", frame.orientation);

   glBindVertexArray(_vaoId);
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   if (_texture != nullptr) {
      _texture->Select();
   }
   this->vertexStrategy->Render(GL_TRIANGLES);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}

