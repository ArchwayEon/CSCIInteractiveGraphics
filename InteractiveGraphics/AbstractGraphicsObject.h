#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT
#include "AbstractGraphicsShader.h"
#include <glm/glm.hpp>
#include "AbstractTexture.h"

class AbstractGraphicsObject
{
protected:
   AbstractGraphicsShader* _shader;
   AbstractTexture* _texture;

public:
   AbstractGraphicsObject() : _shader(nullptr), _texture(nullptr) {}
   AbstractGraphicsObject(AbstractGraphicsShader* shader, AbstractTexture* texture = nullptr) :
      _shader(shader), _texture(nullptr) {}
   virtual ~AbstractGraphicsObject() {}
   virtual void SetShader(AbstractGraphicsShader* shader) {
      _shader = shader;
   }
   virtual void SetTexture(AbstractTexture* texture) {
      _texture = texture;
   }
   virtual void Setup() = 0;
   virtual void Render() = 0;
};

#endif

