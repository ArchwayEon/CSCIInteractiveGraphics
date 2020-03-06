#pragma once
#ifndef ABSTRACT_GRAPHICS_SYSTEM
#define ABSTRACT_GRAPHICS_SYSTEM
#include <map>
using std::map;
#include "AbstractGraphicsWindow.h"
#include "AbstractGraphicsObject.h"
#include "AbstractGraphicsShader.h"
#include "BaseCamera.h"

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   BaseCamera* _camera;
   AbstractGraphicsShader* _shader;
   map<string, AbstractGraphicsObject*> _objects;
   string _errorReport;

public:
   AbstractGraphicsSystem() : 
      _window(nullptr), _camera(new BaseCamera()), _shader(nullptr), 
      _errorReport(""){}
   AbstractGraphicsSystem(
      AbstractGraphicsWindow* window, BaseCamera* camera, AbstractGraphicsShader* shader) :
      _window(window), _camera(camera), _shader(shader),
      _errorReport(""){}
   virtual ~AbstractGraphicsSystem();

   string ReportErrors() { return _errorReport; }
   virtual void AddObject(const string& objectName, AbstractGraphicsObject* object) {
      _objects[objectName] = object;
   }
   virtual AbstractGraphicsObject* GetObject(const string& objectName) {
      return _objects[objectName];
   }
   virtual void SetShader(AbstractGraphicsShader* shader) { _shader = shader; }
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;
};

#endif

