#pragma once
#ifndef ABSTRACT_GRAPHICS_SYSTEM
#define ABSTRACT_GRAPHICS_SYSTEM
#include "AbstractGraphicsWindow.h"
#include "AbstractGraphicsObject.h"

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   AbstractGraphicsObject* _object;

public:
   AbstractGraphicsSystem() : _window(nullptr), _object(nullptr) {}
   AbstractGraphicsSystem(AbstractGraphicsWindow* window) :
      _window(window), _object(nullptr) {}
   virtual ~AbstractGraphicsSystem();
   virtual void SetObject(AbstractGraphicsObject* object) { _object = object; }
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;
};

#endif

