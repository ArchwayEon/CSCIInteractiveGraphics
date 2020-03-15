#pragma once
#ifndef POLYGON_MESH
#define POLYGON_MESH
#include "AbstractMesh.h"
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

class PolygonMesh :
   public AbstractMesh
{
protected:
   vector<VertexPCNT> _vertices;

public:
   virtual void AddVertex(const VertexPCNT& vertex) { _vertices.push_back(vertex); }
   size_t GetSizeInBytes() const;
   size_t GetSizeInBytesOneVertex() const;
   size_t GetSizeInBytesDataItem() const;
   void* GetData();
   void SetTextureCoord(int index, float s, float t) {
      _vertices[index].tex = { s, t };
   }
};
#endif

