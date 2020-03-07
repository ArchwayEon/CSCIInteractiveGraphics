#pragma once
#ifndef ABSTRACT_GRAPHICS_SYSTEM
#define ABSTRACT_GRAPHICS_SYSTEM
#include <map>
using std::map;
#include "AbstractGraphicsWindow.h"
#include "AbstractGraphicsObject.h"
#include "AbstractGraphicsShader.h"
#include "BaseCamera.h"
#include "AbstractTimer.h"

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   BaseCamera* _camera;
   AbstractTimer* _timer;
   map<string, AbstractGraphicsShader*> _shaders;
   map<string, AbstractGraphicsObject*> _objects;
   string _errorReport;

public:
   AbstractGraphicsSystem() : 
      _window(nullptr), _camera(new BaseCamera()), _timer(nullptr),
      _errorReport(""){}
   AbstractGraphicsSystem(
      AbstractGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer) :
      _window(window), _camera(camera), _timer(timer),
      _errorReport(""){}
   virtual ~AbstractGraphicsSystem();

   string ReportErrors() { return _errorReport; }
   virtual void AddObject(const string& objectName, AbstractGraphicsObject* object, const string& shaderName);
   virtual void RemoveObject(const string& objectName);
   virtual AbstractGraphicsObject* GetGraphicsObject(const string& objectName) {
      return _objects[objectName];
   }
   virtual void AddShader(string shaderName, AbstractGraphicsShader* shader);
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;
};

#endif

