#pragma once
#ifndef ABSTRACT_VERTEX_STRATEGY
#define ABSTRACT_VERTEX_STRATEGY

class AbstractVertexStrategy
{
public:
   virtual void SetupBuffer(unsigned int handle) = 0;
   virtual void SetupIndexBuffer(unsigned int handle) {}
   virtual void Render(unsigned int primitiveType) {};
   virtual void RenderWithIndex(unsigned int handle, unsigned int primitiveType) {}

protected:
   // Instructs the GPU how to interpret the buffer
   // location - should match the location in the vertex shader code
   // count - the number of components of the item
   // bytesToNext - the number of bytes to the next item
   // offset - the number of bytes to the first item
   virtual void SetBufferInterpretation(
      unsigned int location, unsigned int count,
      unsigned int bytesToNext, unsigned char offset) = 0;
};

#endif

