#pragma once
#ifndef BACK_FORTH_ANIMATION
#define BACK_FORTH_ANIMATION
#include "AbstractAnimation.h"

class BackForthAnimation :
   public AbstractAnimation
{
protected:
   enum class MoveState { Forward, Backward };
protected:
   float _speed;
   float _distance;
   float _distanceMoved;
   MoveState _moveState;

public:
   BackForthAnimation(float speed, float distance);

   void Update(float elapsedSeconds);
};

#endif

