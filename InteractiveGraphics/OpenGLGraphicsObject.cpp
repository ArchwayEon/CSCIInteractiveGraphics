#include "OpenGLGraphicsObject.h"
#include "GLSLGraphicsShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLVertexStrategy.h"

OpenGLGraphicsObject::~OpenGLGraphicsObject()
{
}

void OpenGLGraphicsObject::Setup()
{
   auto vertexStrategy = (OpenGLVertexStrategy*)this->vertexStrategy;
   vertexStrategy->CreateVAO();
   vertexStrategy->SelectVAO();
   vertexStrategy->CreateVBO();
   vertexStrategy->SetupBuffer();
   if (_texture != nullptr) {
      _texture->Setup();
   }
   vertexStrategy->UnselectVBO();
   vertexStrategy->UnselectVAO();
}

void OpenGLGraphicsObject::Render()
{
   auto shader = (GLSLGraphicsShader*)_shader;
   shader->Select();
   shader->SendMatricesToGPU();
   shader->SendMatrixToGPU("world", frame.orientation);
   shader->SendFloatToGPU("materialAmbientIntensity", material.ambientIntensity);
   shader->SendFloatToGPU("materialSpecularIntensity", material.specularIntensity);
   shader->SendFloatToGPU("materialShininess", material.shininess);

   auto vertexStrategy = (OpenGLVertexStrategy*)this->vertexStrategy;
   vertexStrategy->SelectVAO();
   vertexStrategy->SelectVBO();
   if (_texture != nullptr) {
      _texture->Select();
   }
   vertexStrategy->Render(GL_TRIANGLES);
   vertexStrategy->UnselectAll();
}

