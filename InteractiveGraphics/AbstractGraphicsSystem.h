#pragma once
#ifndef ABSTRACT_GRAPHICS_SYSTEM
#define ABSTRACT_GRAPHICS_SYSTEM
#include "AbstractGraphicsWindow.h"
#include "AbstractGraphicsObject.h"
#include "AbstractGraphicsShader.h"

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   AbstractGraphicsShader* _shader;
   AbstractGraphicsObject* _object;
   string _errorReport;

public:
   AbstractGraphicsSystem() : 
      _window(nullptr), _object(nullptr), 
      _shader(nullptr), _errorReport("") {}
   AbstractGraphicsSystem(AbstractGraphicsWindow* window, AbstractGraphicsShader* shader) :
      _window(window), _object(nullptr), 
      _shader(shader), _errorReport("") {}
   virtual ~AbstractGraphicsSystem();
   string ReportErrors() { return _errorReport; }

   virtual void SetObject(AbstractGraphicsObject* object) { _object = object; }
   virtual void SetShader(AbstractGraphicsShader* shader) { _shader = shader; }
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;
};

#endif

