#pragma once
#ifndef OPENGL_VERTEXPCNT_STRATEGY
#define OPENGL_VERTEXPCNT_STRATEGY
#include "OpenGLVertexStrategy.h"
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

class OpenGLVertexPCNTStrategy :
   public OpenGLVertexStrategy
{
protected:
   vector<VertexPCNT> _vertices;

public:
   OpenGLVertexPCNTStrategy();
   virtual void AddVertex(const VertexPCNT& vertex) { _vertices.push_back(vertex); }
   void SetupBuffer();
   void Render(unsigned int primitiveType);
   void SetTextureCoord(int index, float s, float t) {
      _vertices[index].tex = { s, t };
   }

protected:
   size_t GetSizeOfVertex() { return sizeof(VertexPCNT); }
};

#endif

