#pragma once
#ifndef ABSTRACT_VERTEX_STRATEGY
#define ABSTRACT_VERTEX_STRATEGY
class AbstractMesh;
class AbstractVertexStrategy
{
protected:
   AbstractMesh* _mesh;

public:
   AbstractVertexStrategy(AbstractMesh* mesh = nullptr);
   virtual ~AbstractVertexStrategy();
   virtual AbstractMesh* GetMesh() { return _mesh; }
   virtual void SetMesh(AbstractMesh* mesh);
   virtual void SetupBuffer() = 0;
   virtual void SetupIndexBuffer() {}
   virtual void Render(unsigned int primitiveType) {};

protected:
   // Instructs the GPU how to interpret the buffer
   // location - should match the location in the vertex shader code
   // count - the number of components of the item
   // bytesToNext - the number of bytes to the next item
   // offset - the number of bytes to the first item
   virtual void SetBufferInterpretation(
      unsigned int location, unsigned int count,
      size_t bytesToNext, size_t offset) = 0;
};

#endif

