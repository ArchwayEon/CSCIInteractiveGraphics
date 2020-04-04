#pragma once
#ifndef OPENGL_VERTEXPCN_STRATEGY
#define OPENGL_VERTEXPCN_STRATEGY
#include "OpenGLVertexStrategy.h"

class AbstractMesh;

class OpenGLVertexPCNStrategy :
   public OpenGLVertexStrategy
{
public:
   OpenGLVertexPCNStrategy(AbstractMesh* mesh = nullptr);
   virtual ~OpenGLVertexPCNStrategy();
   void SetupBuffer();
   void Render(unsigned int primitiveType);

protected:
   size_t GetOffset(OffsetType offsetType);
};

#endif

