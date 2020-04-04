#pragma once
#ifndef ABSTRACT_MESH
#define ABSTRACT_MESH
#include <stddef.h>

class AbstractMesh
{
public:
   virtual size_t GetSizeInBytes() const = 0;
   virtual size_t GetSizeInBytesOneVertex() const = 0;
   virtual size_t GetSizeInBytesDataItem() const = 0;
   virtual void* GetData() = 0;
};
#endif
