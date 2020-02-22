#pragma once
#ifndef OPENGL_GRAPHICS_OBJECT
#define OPENGL_GRAPHICS_OBJECT

#include "AbstractGraphicsObject.h"
#include <glad/glad.h> 
#include "GraphicsStructures.h"

class OpenGLGraphicsObject :
   public AbstractGraphicsObject
{
private:
   GLuint _vaoId, _vboId;
   GLsizei _arraySize;
   Vertex * _objectData;

public:
   OpenGLGraphicsObject() : 
      _vaoId(0), _vboId(0), _arraySize(0), _objectData(nullptr)
   {}
   OpenGLGraphicsObject(AbstractGraphicsShader* shader) : 
      AbstractGraphicsObject(shader), _vaoId(0), _vboId(0), 
      _arraySize(0), _objectData(nullptr)
   {}
   ~OpenGLGraphicsObject();
   void SetObjectData(Vertex* objectData, GLsizei size) { 
      _objectData = objectData; 
      _arraySize = size;
   }
   void Setup();
   void Render();
};

#endif

