#pragma once
#ifndef OPENGL_VERTEXPCT_STRATEGY
#define OPENGL_VERTEXPCT_STRATEGY
#include "OpenGLVertexStrategy.h"
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

class OpenGLVertexPCTStrategy :
   public OpenGLVertexStrategy
{
protected:
   vector<VertexPCT> _vertices;

public:
   virtual void AddVertex(const VertexPCT& vertex) { _vertices.push_back(vertex); }
   virtual void SetColor(int facet, int numberOfVertices, RGBA color);
   void SetupBuffer(unsigned int handle);
   void Render(unsigned int primitiveType);
};

#endif

