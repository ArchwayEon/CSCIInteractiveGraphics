#pragma once
#ifndef ROTATE_ANIMATION
#define ROTATE_ANIMATION
#include "AbstractAnimation.h"
#include <glm\glm.hpp>

class RotateAnimation :
   public AbstractAnimation
{
protected:
   double _degreesPerSecond;
   glm::vec3 _axis;

public:
   RotateAnimation(double degreesPerSecond = 90.0, glm::vec3 axis = { 0.0f, 1.0f, 0.0f })
      : _degreesPerSecond(degreesPerSecond), _axis(axis) {}

   void Update(double elapsedSeconds);
};

#endif

