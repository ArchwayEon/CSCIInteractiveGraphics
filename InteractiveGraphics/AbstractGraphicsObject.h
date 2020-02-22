#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT

class AbstractGraphicsObject
{
public:
   virtual ~AbstractGraphicsObject() {}
   virtual void Setup() = 0;
   virtual void Render(unsigned int shaderProgramId) = 0;
};

#endif

