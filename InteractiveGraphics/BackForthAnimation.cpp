#include "BackForthAnimation.h"
#include <glm\glm.hpp>
#include "AbstractGraphicsObject.h"

BackForthAnimation::BackForthAnimation(float speed, float distance) :
   _speed(speed), _distance(distance), _distanceMoved(0), 
   _moveState(MoveState::Forward)
{
}

void BackForthAnimation::Update(float elapsedSeconds)
{
   float distanceToMove = _speed * elapsedSeconds;
   glm::vec4 forward = this->graphicsObject->frame.orientation[2];
   glm::vec4 backward;
   backward.x = -forward.x;
   backward.y = -forward.y;
   backward.z = -forward.z;

   switch (_moveState) {
   case MoveState::Forward:
      _distanceMoved += distanceToMove;
      if (_distanceMoved >= _distance) {
         _moveState = MoveState::Backward;
         float diff = _distanceMoved - _distance;
         distanceToMove -= diff;
         _distanceMoved = 0;
      }
      this->graphicsObject->frame.Move(forward * distanceToMove);
      break;
   case MoveState::Backward:
      _distanceMoved += distanceToMove;
      if (_distanceMoved >= _distance) {
         _moveState = MoveState::Forward;
         float diff = _distanceMoved - _distance;
         distanceToMove -= diff;
         _distanceMoved = 0;
      }
      this->graphicsObject->frame.Move(backward * distanceToMove);
      break;
   }
}
