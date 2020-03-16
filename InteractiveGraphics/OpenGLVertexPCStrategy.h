#pragma once
#ifndef OPENGL_VERTEXPC_STRATEGY
#define OPENGL_VERTEXPC_STRATEGY
#include "AbstractVertexStrategy.h"
#include "OpenGLVertexStrategy.h"
#include <vector>
#include "GraphicsStructures.h"
using std::vector;

class OpenGLVertexPCStrategy :
   public OpenGLVertexStrategy
{
protected:
   vector<VertexPC> _vertices;

public:
   OpenGLVertexPCStrategy();
   virtual void AddVertex(const VertexPC& vertex) { _vertices.push_back(vertex); }
   virtual void SetColor(int facet, int numberOfVertices, RGBA color);
   void SetupBuffer();
   void Render(unsigned int primitiveType);

protected:
   size_t GetSizeOfVertex() { return sizeof(VertexPC); }
};

#endif

