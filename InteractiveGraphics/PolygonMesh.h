#pragma once
#ifndef POLYGON_MESH
#define POLYGON_MESH
#include "AbstractMesh.h"
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

template <class T>
class PolygonMesh :
   public AbstractMesh
{
protected:
   vector<T> _vertices;

public:
   virtual void AddVertex(const T& vertex) { 
      _vertices.push_back(vertex); 
   }
   size_t GetSizeInBytes() const {
      return _vertices.size() * sizeof(T);
   }
   size_t GetSizeInBytesOneVertex() const {
      return sizeof(T);
   }
   size_t GetSizeInBytesDataItem() const {
      return sizeof(float);
   }
   void* GetData() {
      return &_vertices[0];
   }
   void SetTextureCoord(int index, float s, float t) {
      _vertices[index].tex = { s, t };
   }
};
#endif

