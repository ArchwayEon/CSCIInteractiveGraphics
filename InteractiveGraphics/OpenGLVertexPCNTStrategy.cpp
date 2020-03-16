#include "OpenGLVertexPCNTStrategy.h"

OpenGLVertexPCNTStrategy::OpenGLVertexPCNTStrategy()
{
   _positionOffset = 0;
   _colorOffset = 3;
   _normalOffset = 7;
   _textureOffset = 10;
}

void OpenGLVertexPCNTStrategy::SetupBuffer()
{
   SelectVBO();
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER,
      _vertices.size() * sizeof(VertexPCNT), &_vertices[0],
      GL_STATIC_DRAW);
}

void OpenGLVertexPCNTStrategy::Render(unsigned int primitiveType)
{
   // Positions
   SetBufferInterpretation(0, 3, sizeof(VertexPCNT), _positionOffset);
   // Colors
   SetBufferInterpretation(1, 4, sizeof(VertexPCNT), (sizeof(GLfloat) * _colorOffset));
   // Normals
   SetBufferInterpretation(2, 3, sizeof(VertexPCNT), (sizeof(GLfloat) * _normalOffset));
   // Texture Coordinates
   SetBufferInterpretation(3, 2, sizeof(VertexPCNT), (sizeof(GLfloat) * _textureOffset));
   glDrawArrays(primitiveType, 0, (GLsizei)_vertices.size());
}
