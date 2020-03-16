#pragma once
#ifndef ABSTRACT_VERTEX_STRATEGY
#define ABSTRACT_VERTEX_STRATEGY

class AbstractVertexStrategy
{
protected:
   size_t _positionOffset;
   size_t _colorOffset;
   size_t _normalOffset;
   size_t _textureOffset;

public:
   AbstractVertexStrategy() :
      _positionOffset(0), _colorOffset(0), _normalOffset(0), _textureOffset(0) 
   {}
   virtual void SetPositionOffset(unsigned int offset) { _positionOffset = offset; }
   virtual void SetColorOffset(unsigned int offset) { _colorOffset = offset; }
   virtual void SetNormalOffset(unsigned int offset) { _normalOffset = offset; }
   virtual void SetTextureOffset(unsigned int offset) { _textureOffset = offset; }
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
   virtual size_t GetSizeOfVertex() = 0;
};

#endif

