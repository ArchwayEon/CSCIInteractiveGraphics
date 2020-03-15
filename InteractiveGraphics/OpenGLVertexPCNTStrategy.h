#pragma once
#ifndef OPENGL_VERTEXPCNT_STRATEGY
#define OPENGL_VERTEXPCNT_STRATEGY
#include "OpenGLVertexStrategy.h"

class AbstractMesh;

class OpenGLVertexPCNTStrategy :
   public OpenGLVertexStrategy
{
public:
   OpenGLVertexPCNTStrategy(AbstractMesh* mesh = nullptr);
   virtual ~OpenGLVertexPCNTStrategy();
   void SetupBuffer();
   void Render(unsigned int primitiveType);
};

#endif

