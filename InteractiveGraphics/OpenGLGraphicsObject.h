#pragma once
#ifndef OPENGL_GRAPHICS_OBJECT
#define OPENGL_GRAPHICS_OBJECT

#include "AbstractGraphicsObject.h"
#include <glad/glad.h> 
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

class OpenGLGraphicsObject :
   public AbstractGraphicsObject
{
private:
   GLuint _vaoId, _vboId;
   vector<Vertex> _vertices;

public:
   OpenGLGraphicsObject() : 
      _vaoId(0), _vboId(0)
   {}
   OpenGLGraphicsObject(AbstractGraphicsShader* shader) : 
      AbstractGraphicsObject(shader), _vaoId(0), _vboId(0)
   {}
   ~OpenGLGraphicsObject();
   void AddVertex(const Vertex& vertex) { _vertices.push_back(vertex); }
   void Setup();
   void Render();
};

#endif

