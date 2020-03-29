#include "OpenGLVertexPCStrategy.h"
#include <glad\glad.h>

OpenGLVertexPCStrategy::OpenGLVertexPCStrategy() : OpenGLVertexStrategy()
{
}

void OpenGLVertexPCStrategy::SetColor(int facet, int numberOfVertices, RGBA color)
{
   vector<int> indexes;
   int start = facet * numberOfVertices;
   int end = start + numberOfVertices;
   for (int i = start; i < end; i++) {
      _vertices[i].red = color.red;
      _vertices[i].green = color.green;
      _vertices[i].blue = color.blue;
   }
}

void OpenGLVertexPCStrategy::SetupBuffer()
{
   SelectVBO();
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER, 
      _vertices.size() * GetSizeOfVertex(), &_vertices[0], 
      GL_STATIC_DRAW);
}

void OpenGLVertexPCStrategy::Render(unsigned int primitiveType)
{
   size_t vertexSize = GetSizeOfVertex();
   // Positions
   SetBufferInterpretation(0, 3, vertexSize, GetOffset(OffsetType::Position));
   // Colors
   SetBufferInterpretation(1, 3, vertexSize, (sizeof(GLfloat) * GetOffset(OffsetType::Color)));
   glDrawArrays(primitiveType, 0, (GLsizei)_vertices.size());
}

size_t OpenGLVertexPCStrategy::GetOffset(OffsetType offsetType)
{
   size_t offset = 0;
   switch (offsetType) {
   case OffsetType::Position:
      offset = 0;
      break;
   case OffsetType::Color:
      offset = 3;
      break;
   }
   return offset;
}

