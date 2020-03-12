#pragma once
#ifndef ABSTRACT_ANIMATION
#define ABSTRACT_ANIMATION

class AbstractGraphicsObject;

class AbstractAnimation
{
public:
   AbstractGraphicsObject* graphicsObject;

public:
   AbstractAnimation() : graphicsObject(nullptr) {}
   virtual void Update(double elapsedSeconds) = 0;
};

#endif

