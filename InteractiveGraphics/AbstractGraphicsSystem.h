#pragma once
#ifndef ABSTRACT_GRAPHICS_SYSTEM
#define ABSTRACT_GRAPHICS_SYSTEM
#include <map>
using std::map;
#include "AbstractGraphicsWindow.h"
#include "AbstractGraphicsObject.h"
#include "AbstractGraphicsShader.h"

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   AbstractGraphicsShader* _shader;
   map<string, AbstractGraphicsObject*> _objects;
   float _aspectRatio;
   string _errorReport;

public:
   AbstractGraphicsSystem() : 
      _window(nullptr), _shader(nullptr), _errorReport(""), _aspectRatio(1.0f) {}
   AbstractGraphicsSystem(AbstractGraphicsWindow* window, AbstractGraphicsShader* shader) :
      _window(window), _shader(shader), _errorReport(""), _aspectRatio(1.0f) {}
   virtual ~AbstractGraphicsSystem();
   string ReportErrors() { return _errorReport; }
   virtual void AddObject(const string& objectName, AbstractGraphicsObject* object) {
      _objects[objectName] = object;
   }
   virtual void SetShader(AbstractGraphicsShader* shader) { _shader = shader; }
   
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;
};

#endif

