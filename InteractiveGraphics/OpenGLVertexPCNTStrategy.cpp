#include "OpenGLVertexPCNTStrategy.h"
#include "PolygonMesh.h"

OpenGLVertexPCNTStrategy::OpenGLVertexPCNTStrategy(AbstractMesh* mesh) :
   OpenGLVertexStrategy(mesh)
{
}

OpenGLVertexPCNTStrategy::~OpenGLVertexPCNTStrategy()
{
}

void OpenGLVertexPCNTStrategy::SetupBuffer()
{
   SelectVBO();
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER, _mesh->GetSizeInBytes(), _mesh->GetData(),
      GL_STATIC_DRAW);
}

void OpenGLVertexPCNTStrategy::Render(unsigned int primitiveType)
{
   auto sizeOneVertex = _mesh->GetSizeInBytesOneVertex();
   auto sizeDataItem = _mesh->GetSizeInBytesDataItem();
   // Positions
   SetBufferInterpretation(0, 3, sizeOneVertex, 0);
   // Colors
   SetBufferInterpretation(1, 4, sizeOneVertex, (sizeDataItem * 3));
   // Normals
   SetBufferInterpretation(2, 3, sizeOneVertex, (sizeDataItem * 7));
   // Texture Coordinates
   SetBufferInterpretation(3, 2, sizeOneVertex, (sizeDataItem * 10));
   glDrawArrays(primitiveType, 0, (GLsizei)_mesh->GetSizeInBytes());
}
