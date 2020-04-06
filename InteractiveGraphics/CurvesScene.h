#pragma once
#ifndef CURVES_SCENE
#define CURVES_SCENE

#include "BaseGraphicsScene.h"
class CurvesScene :
   public BaseGraphicsScene
{
public:
   CurvesScene(AbstractGraphicsSystem* graphics, BaseCamera* camera)
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

