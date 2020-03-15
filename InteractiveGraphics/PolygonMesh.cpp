#include "PolygonMesh.h"

size_t PolygonMesh::GetSizeInBytes() const
{
   return _vertices.size() * sizeof(VertexPCNT);
}

size_t PolygonMesh::GetSizeInBytesOneVertex() const
{
   return sizeof(VertexPCNT);
}

size_t PolygonMesh::GetSizeInBytesDataItem() const
{
   return sizeof(float);
}

void* PolygonMesh::GetData()
{
   return &_vertices[0];
}
