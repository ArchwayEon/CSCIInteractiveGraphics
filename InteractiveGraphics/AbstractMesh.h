#pragma once
#ifndef ABSTRACT_MESH
#define ABSTRACT_MESH
#include <stddef.h>
class AbstractMesh
{
public:
   virtual inline size_t GetSizeInBytes() const = 0;
   virtual inline size_t GetSizeInBytesOneVertex() const = 0;
   virtual inline size_t GetSizeInBytesDataItem() const = 0;
   virtual inline void* GetData() = 0;
};
#endif
