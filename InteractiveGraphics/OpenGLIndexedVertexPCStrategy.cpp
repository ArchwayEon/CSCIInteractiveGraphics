#include "OpenGLIndexedVertexPCStrategy.h"
#include <glad\glad.h>

void OpenGLIndexedVertexPCStrategy::SetupIndexBuffer(unsigned int handle)
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      _indexes.size() * sizeof(unsigned int), 
      &_indexes[0], GL_STATIC_DRAW);
}

void OpenGLIndexedVertexPCStrategy::RenderWithIndex(unsigned int handle, unsigned int primitiveType)
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
   glDrawElements(primitiveType, (GLsizei)_indexes.size(), GL_UNSIGNED_INT, 0);
}

