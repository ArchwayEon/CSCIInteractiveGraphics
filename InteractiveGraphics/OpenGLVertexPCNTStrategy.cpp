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
   SetBufferInterpretation(0, 3, sizeOneVertex, GetOffset(OffsetType::Position));
   // Colors
   SetBufferInterpretation(1, 4, sizeOneVertex, (sizeDataItem * GetOffset(OffsetType::Color)));
   // Normals
   SetBufferInterpretation(2, 3, sizeOneVertex, (sizeDataItem * GetOffset(OffsetType::Normal)));
   // Texture Coordinates
   SetBufferInterpretation(3, 2, sizeOneVertex, (sizeDataItem * GetOffset(OffsetType::Texture)));
   glDrawArrays(primitiveType, 0, (GLsizei)_mesh->GetSizeInBytes());
}

size_t OpenGLVertexPCNTStrategy::GetOffset(OffsetType offsetType)
{
   size_t offset = 0;
   switch (offsetType) {
   case OffsetType::Position:
      offset = 0;
      break;
   case OffsetType::Color:
      offset = 3;
      break;
   case OffsetType::Normal:
      offset = 7;
      break;
   case OffsetType::Texture:
      offset = 10;
      break;
   }
   return offset;
}
