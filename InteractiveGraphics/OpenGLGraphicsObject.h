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
   vector<Vertex> _vertices;

public:
   ReferenceFrame frame;

public:
   OpenGLGraphicsObject() : 
      _vaoId(0), _vboId(0), frame()
   {}
   OpenGLGraphicsObject(AbstractGraphicsShader* shader) : 
      AbstractGraphicsObject(shader), _vaoId(0), _vboId(0), frame()
   {}
   ~OpenGLGraphicsObject();
   void AddVertex(const Vertex& vertex) { _vertices.push_back(vertex); }
   void SetColor(int facet, int numberOfVertices, RGBA color);
   void Setup();
   void Render();
};

#endif

