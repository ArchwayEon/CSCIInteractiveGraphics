#pragma once
#ifndef OPENGL_VERTEXPC_STRATEGY
#define OPENGL_VERTEXPC_STRATEGY
#include "AbstractVertexStrategy.h"
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

class OpenGLVertexPCStrategy :
   public AbstractVertexStrategy
{
protected:
   vector<Vertex> _vertices;

public:
   virtual void AddVertex(const Vertex& vertex) { _vertices.push_back(vertex); }
   virtual void SetColor(int facet, int numberOfVertices, RGBA color);
   void SetupBuffer(unsigned int handle);
   void Render(unsigned int primitiveType);
};

#endif

