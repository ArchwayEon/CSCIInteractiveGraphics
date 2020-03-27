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
   OpenGLVertexPCTStrategy();
   virtual void AddVertex(const VertexPCT& vertex) { _vertices.push_back(vertex); }
   virtual void SetColor(int facet, int numberOfVertices, RGBA color);
   void SetupBuffer();
   void Render(unsigned int primitiveType);
   void SetTextureCoord(int index, float s, float t) {
      _vertices[index].tex = { s, t };
   }

protected:
   size_t GetSizeOfVertex() { return sizeof(VertexPCT); }

};

#endif

