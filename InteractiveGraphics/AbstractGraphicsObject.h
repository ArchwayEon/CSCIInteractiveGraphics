#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT
#include "AbstractGraphicsShader.h"
#include <glm/glm.hpp>

class AbstractGraphicsObject
{
protected:
   AbstractGraphicsShader* _shader;

public:
   AbstractGraphicsObject() : _shader(nullptr) {}
   AbstractGraphicsObject(AbstractGraphicsShader* shader) :
      _shader(shader) {}
   virtual ~AbstractGraphicsObject() {}
   virtual void SetShader(AbstractGraphicsShader* shader) {
      _shader = shader;
   }
   virtual void Setup() = 0;
   virtual void Render() = 0;
   virtual void Rotate(float degrees, const glm::vec3& axis) = 0;
   virtual void RotateWorld(float degrees, const glm::vec3& axis) = 0;
   virtual void Move(const glm::vec3& vector) = 0;
};

#endif

