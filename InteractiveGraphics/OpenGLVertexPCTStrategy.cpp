#include "OpenGLVertexPCTStrategy.h"
#include <glad\glad.h>

OpenGLVertexPCTStrategy::OpenGLVertexPCTStrategy() : OpenGLVertexStrategy()
{
}

void OpenGLVertexPCTStrategy::SetColor(int facet, int numberOfVertices, RGBA color)
{
   vector<int> indexes;
   int start = facet * numberOfVertices;
   int end = start + numberOfVertices;
   for (int i = start; i < end; i++) {
      _vertices[i].color.red = color.red;
      _vertices[i].color.green = color.green;
      _vertices[i].color.blue = color.blue;
      _vertices[i].color.alpha = color.alpha;
   }
}

void OpenGLVertexPCTStrategy::SetupBuffer()
{
   SelectVBO();
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER,
      _vertices.size() * GetSizeOfVertex(), &_vertices[0],
      GL_STATIC_DRAW);
}

void OpenGLVertexPCTStrategy::Render(unsigned int primitiveType)
{
   size_t vertexSize = GetSizeOfVertex();
   // Positions
   SetBufferInterpretation(0, 3, vertexSize, GetOffset(OffsetType::Position));
   // Colors
   SetBufferInterpretation(1, 4, vertexSize, (sizeof(GLfloat) * GetOffset(OffsetType::Color)));
   // Texture Coordinates
   SetBufferInterpretation(2, 2, vertexSize, (sizeof(GLfloat) * GetOffset(OffsetType::Texture)));
   glDrawArrays(primitiveType, 0, (GLsizei)_vertices.size());
}

size_t OpenGLVertexPCTStrategy::GetOffset(OffsetType offsetType)
{
   size_t offset = 0;
   switch (offsetType) {
   case OffsetType::Position:
      offset = 0;
      break;
   case OffsetType::Color:
      offset = 3;
      break;
   case OffsetType::Texture:
      offset = 7;
      break;
   }
   return offset;
}
