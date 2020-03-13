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
#include "BaseGraphicsScene.h"

class BaseGraphicsScene;

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   BaseCamera* _camera;
   AbstractTimer* _timer;
   map<string, AbstractGraphicsShader*> _shaders;
   //map<string, AbstractGraphicsObject*> _objects;
   map<string, AbstractTexture*> _textures;
   string _errorReport;

public:
   BaseGraphicsScene* scene;

public:
   AbstractGraphicsSystem();
   AbstractGraphicsSystem(AbstractGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer);
   virtual ~AbstractGraphicsSystem();

   string ReportErrors() { return _errorReport; }
   virtual void AddShader(string shaderName, AbstractGraphicsShader* shader);
   virtual void AddTexture(string textureName, AbstractTexture* texture);
   virtual AbstractTexture* GetTexture(const string& textureName) {
      return _textures[textureName];
   }
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;

protected:
   virtual void Init();
};

#endif

