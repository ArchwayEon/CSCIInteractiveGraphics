#pragma once
#ifndef MY_SCENE
#define MY_SCENE

#include "BaseGraphicsScene.h"
class AbstractGraphicsSystem;
class BaseCamera;

class MyScene :
   public BaseGraphicsScene
{
public:
   MyScene(AbstractGraphicsSystem* graphics, BaseCamera* camera)
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

