#pragma once
#ifndef OPENGL_INDEXED_GRAPHICS_OBJECT
#define OPENGL_INDEXED_GRAPHICS_OBJECT
#include "OpenGLGraphicsObject.h"

class OpenGLIndexedGraphicsObject :
   public OpenGLGraphicsObject
{
protected:
   GLuint _indexVbo;

public:
   OpenGLIndexedGraphicsObject() :
      OpenGLGraphicsObject(), _indexVbo(0)
   {}
   OpenGLIndexedGraphicsObject(AbstractGraphicsShader* shader) :
      OpenGLGraphicsObject(shader), _indexVbo(0)
   {}
   void Setup();
   void Render();
};

#endif

