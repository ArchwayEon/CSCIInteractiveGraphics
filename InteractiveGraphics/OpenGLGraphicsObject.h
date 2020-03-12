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
public:
   OpenGLGraphicsObject() : 
      AbstractGraphicsObject()
   {}
   OpenGLGraphicsObject(
      AbstractGraphicsShader* shader,
      AbstractTexture* texture = nullptr) :
      AbstractGraphicsObject(shader, texture)
   {}
   ~OpenGLGraphicsObject();
   void Setup();
   void Render();
};

#endif

