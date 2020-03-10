#pragma once
#ifndef OPENGL_INDEXED_VERTEXPC_STRATEGY
#define OPENGL_INDEXED_VERTEXPC_STRATEGY
#include "OpenGLVertexPCStrategy.h"

class OpenGLIndexedVertexPCStrategy :
   public OpenGLVertexPCStrategy
{
protected:
   vector<unsigned int> _indexes;

public:
   OpenGLIndexedVertexPCStrategy() {}
   void AddIndex(unsigned int index) { _indexes.push_back(index); }
   void SetupIndexBuffer();
   void Render(unsigned int primitiveType);
};
#endif

