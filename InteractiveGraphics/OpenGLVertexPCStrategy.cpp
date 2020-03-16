#include "OpenGLVertexPCStrategy.h"
#include <glad\glad.h>

OpenGLVertexPCStrategy::OpenGLVertexPCStrategy() : OpenGLVertexStrategy()
{
   _positionOffset = 0;
   _colorOffset = 3;
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
      _vertices.size() * sizeof(VertexPC), &_vertices[0], 
      GL_STATIC_DRAW);
}

void OpenGLVertexPCStrategy::Render(unsigned int primitiveType)
{
   // Positions
   SetBufferInterpretation(0, 3, sizeof(VertexPC), _positionOffset);
   // Colors
   SetBufferInterpretation(1, 3, sizeof(VertexPC), (sizeof(GLfloat) * _colorOffset));
   glDrawArrays(primitiveType, 0, (GLsizei)_vertices.size());
}

