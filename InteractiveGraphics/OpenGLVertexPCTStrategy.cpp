#include "OpenGLVertexPCTStrategy.h"
#include <glad\glad.h>

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

void OpenGLVertexPCTStrategy::SetupBuffer(unsigned int handle)
{
   // Bind the object to the binding target
   glBindBuffer(GL_ARRAY_BUFFER, handle);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER,
      _vertices.size() * sizeof(VertexPCT), &_vertices[0],
      GL_STATIC_DRAW);
}

void OpenGLVertexPCTStrategy::Render(unsigned int primitiveType)
{
   // Positions
   SetBufferInterpretation(0, 3, sizeof(VertexPCT), 0);
   // Colors
   SetBufferInterpretation(1, 4, sizeof(VertexPCT), (sizeof(GLfloat) * 3));
   // Texture Coordinates
   SetBufferInterpretation(2, 2, sizeof(VertexPCT), (sizeof(GLfloat) * 7));
   glDrawArrays(primitiveType, 0, (GLsizei)_vertices.size());
}
