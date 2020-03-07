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
};

#endif

