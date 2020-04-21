#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT
#include "AbstractGraphicsShader.h"
#include <glm/glm.hpp>
#include "AbstractTexture.h"
#include "AbstractVertexStrategy.h"
#include "ReferenceFrame.h"
#include "GraphicsStructures.h"
#include "BoundingSphere.h"

class AbstractAnimation;

class AbstractGraphicsObject
{
protected:
   AbstractGraphicsShader* _shader;
   AbstractTexture* _texture;

public:
   AbstractVertexStrategy* vertexStrategy;
   ReferenceFrame frame;
   AbstractAnimation* animation;
   Material material;
   bool isVisible;
   BoundingSphere boundingSphere;

public:
   AbstractGraphicsObject();
   AbstractGraphicsObject(AbstractGraphicsShader* shader, AbstractTexture* texture = nullptr);
   virtual ~AbstractGraphicsObject();
   virtual void SetShader(AbstractGraphicsShader* shader) {
      _shader = shader;
   }
   virtual AbstractGraphicsShader* GetShader() {
      return _shader;
   }
   virtual void SetTexture(AbstractTexture* texture) {
      _texture = texture;
   }
   virtual void Setup() = 0;
   virtual void Render() = 0;
   virtual void Update(double elapsedSeconds);

protected:
   virtual void Init();
};

#endif

