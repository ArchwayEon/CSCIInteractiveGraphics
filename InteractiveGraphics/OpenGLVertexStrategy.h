#pragma once
#ifndef OPENGL_VERTEX_STRATEGY
#define OPENGL_VERTEX_STRATEGY
#include "AbstractVertexStrategy.h"
#include <glad\glad.h>
class AbstractMesh;

class OpenGLVertexStrategy :
   public AbstractVertexStrategy
{
protected:
   GLuint _vaoId, _vboId;
   GLuint _indexVboId;

public:
   OpenGLVertexStrategy(AbstractMesh* mesh = nullptr) : 
      AbstractVertexStrategy(mesh),
      _vaoId(0), _vboId(0), _indexVboId(0)
   {}
   ~OpenGLVertexStrategy();

   virtual inline void CreateVAO();
   virtual inline void SelectVAO();
   virtual inline void UnselectVAO();
   virtual inline void CreateVBO();
   virtual inline void SelectVBO();
   virtual inline void UnselectVBO();
   virtual inline void CreateIndexVBO();
   virtual inline void SelectIndexVBO();
   virtual void UnselectAll();

protected:
   virtual void SetBufferInterpretation(
      unsigned int location, unsigned int count,
      size_t bytesToNext, size_t offset);
};

#endif

