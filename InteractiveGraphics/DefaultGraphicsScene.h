#pragma once
#ifndef DEFAULT_GRAPHICS_SCENE
#define DEFAULT_GRAPHICS_SCENE

#include "BaseGraphicsScene.h"
class AbstractGraphicsSystem;
class BaseCamera;

class DefaultGraphicsScene :
   public BaseGraphicsScene
{
public:
   DefaultGraphicsScene(AbstractGraphicsSystem* graphics, BaseCamera* camera)
      : BaseGraphicsScene(graphics, camera) {}
   bool LoadScene();

protected:
   bool LoadShaders();
   bool LoadTextures();
   bool LoadAnimations();
   bool LoadObjects();
   bool LoadLights();
};

#endif

