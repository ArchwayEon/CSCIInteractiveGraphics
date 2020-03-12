#include "RotateAnimation.h"
#include "AbstractGraphicsObject.h"

void RotateAnimation::Update(double elapsedSeconds)
{
   auto deltaDegrees = _degreesPerSecond * elapsedSeconds;
   this->graphicsObject->frame.Rotate((float)deltaDegrees, _axis);
}
