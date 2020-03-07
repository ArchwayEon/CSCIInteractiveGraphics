#pragma once
#ifndef OPENGL_INDEXED_VERTEXPC_STRATEGY
#define OPENGL_INDEXED_VERTEXPC_STRATEGY
#include "OpenGLVertexPCStrategy.h"

class OpenGLIndexedVertexPCStrategy :
   public OpenGLVertexPCStrategy
{
protected:
   vector<unsigned int> _indexes;
   unsigned int _indexVbo;

public:
   OpenGLIndexedVertexPCStrategy() : _indexVbo(0) {}
   void SetIndexVbo(unsigned int indexVbo) { _indexVbo = indexVbo; };
   void AddIndex(unsigned int index) { _indexes.push_back(index); }
   void SetupIndexBuffer(unsigned int handle);
   void RenderWithIndex(unsigned int handle, unsigned int primitiveType);
};
#endif

