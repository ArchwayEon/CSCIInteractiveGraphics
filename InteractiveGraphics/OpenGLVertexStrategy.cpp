#include "OpenGLVertexStrategy.h"
#include <glad\glad.h>
#include <vector>
using std::vector;

OpenGLVertexStrategy::~OpenGLVertexStrategy()
{
   glDeleteVertexArrays(1, &_vaoId);
}

void OpenGLVertexStrategy::CreateVAO()
{
   glGenVertexArrays(1, &_vaoId);
}

inline void OpenGLVertexStrategy::SelectVAO()
{
   glBindVertexArray(_vaoId);
}

inline void OpenGLVertexStrategy::UnselectVAO()
{
   glBindVertexArray(0);
}

inline void OpenGLVertexStrategy::CreateVBO()
{
   glGenBuffers(1, &_vboId);
}

inline void OpenGLVertexStrategy::SelectVBO()
{
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
}

inline void OpenGLVertexStrategy::UnselectVBO()
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline void OpenGLVertexStrategy::CreateIndexVBO()
{
   glGenBuffers(1, &_indexVboId);
}

inline void OpenGLVertexStrategy::SelectIndexVBO()
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVboId);
}

void OpenGLVertexStrategy::UnselectAll()
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}

void OpenGLVertexStrategy::SetBufferInterpretation(
   unsigned int location, unsigned int count, 
   size_t bytesToNext, size_t offset)
{
   glEnableVertexAttribArray(location);
   glVertexAttribPointer(
      location,
      count,        // Number of components
      GL_FLOAT,     // Each component is a 32-bit floating point value
      GL_FALSE,
      (GLsizei)bytesToNext,  // The number of bytes to the next item
      (void*)offset // Byte offset of the first item in the array
   );
}
