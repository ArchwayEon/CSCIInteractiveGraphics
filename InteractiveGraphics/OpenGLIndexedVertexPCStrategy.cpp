#include "OpenGLIndexedVertexPCStrategy.h"
#include <glad\glad.h>

void OpenGLIndexedVertexPCStrategy::SetupIndexBuffer()
{
   SelectIndexVBO();
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      _indexes.size() * sizeof(unsigned int), 
      &_indexes[0], GL_STATIC_DRAW);
}

void OpenGLIndexedVertexPCStrategy::Render(unsigned int primitiveType)
{
   // Positions
   SetBufferInterpretation(0, 3, sizeof(VertexPC), 0);
   // Colors
   SetBufferInterpretation(1, 3, sizeof(VertexPC), (sizeof(GLfloat) * 3));
   SelectIndexVBO();
   glDrawElements(primitiveType, (GLsizei)_indexes.size(), GL_UNSIGNED_INT, 0);
}

