#pragma once
#ifndef OPENGL_GRAPHICS_OBJECT
#define OPENGL_GRAPHICS_OBJECT

#include <glad/glad.h> 
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"

#include <vector>
using std::vector;

class OpenGLGraphicsObject :
   public AbstractGraphicsObject
{
protected:
   unsigned int _primitiveType;

public:
   OpenGLGraphicsObject();
   OpenGLGraphicsObject(
      AbstractGraphicsShader* shader,
      AbstractTexture* texture = nullptr);
   ~OpenGLGraphicsObject();
   virtual void SetPrimitiveType(unsigned int primitiveType) {
      _primitiveType = primitiveType;
   }
   void Setup();
   void Render();

protected:
   void Init();
};

#endif

