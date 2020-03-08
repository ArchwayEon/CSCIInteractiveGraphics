#pragma once
#ifndef OPENGL_VERTEX_STRATEGY
#define OPENGL_VERTEX_STRATEGY
#include "AbstractVertexStrategy.h"

class OpenGLVertexStrategy :
   public AbstractVertexStrategy
{
public:

protected:
   virtual void SetBufferInterpretation(
      unsigned int location, unsigned int count,
      unsigned int bytesToNext, unsigned char offset);
};

#endif

