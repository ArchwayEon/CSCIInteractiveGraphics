#pragma once
#ifndef OPENGL_GRAPHICS_OBJECT
#define OPENGL_GRAPHICS_OBJECT

#include <glad/glad.h> 
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"
#include "ReferenceFrame.h"
#include <vector>
using std::vector;

class OpenGLGraphicsObject :
   public AbstractGraphicsObject
{
protected:
   GLuint _vaoId, _vboId;

public:
   ReferenceFrame frame;

public:
   OpenGLGraphicsObject() : 
      AbstractGraphicsObject(),
      _vaoId(0), _vboId(0), frame()
   {}
   OpenGLGraphicsObject(
      AbstractGraphicsShader* shader,
      AbstractTexture* texture = nullptr) :
      AbstractGraphicsObject(shader, texture), _vaoId(0), _vboId(0), frame()
   {}
   ~OpenGLGraphicsObject();
   void Setup();
   void Render();
};

#endif

