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
#include "AbstractAnimation.h"

class BaseGraphicsScene;

class AbstractGraphicsSystem
{
protected:
   AbstractGraphicsWindow* _window;
   BaseCamera* _camera;
   AbstractTimer* _timer;
   map<string, AbstractGraphicsShader*> _shaders;
   map<string, AbstractTexture*> _textures;
   map<string, AbstractAnimation*> _animations;
   string _errorReport;

public:
   BaseGraphicsScene* scene;

public:
   AbstractGraphicsSystem();
   AbstractGraphicsSystem(AbstractGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer);
   virtual ~AbstractGraphicsSystem();
   virtual AbstractGraphicsWindow* GetWindow() {
      return _window;
   }
   string ReportErrors() { return _errorReport; }
   virtual void AddShader(const string& shaderName, AbstractGraphicsShader* shader);
   virtual void AddTexture(const string& textureName, AbstractTexture* texture);
   virtual void AddAnimation(const string& animationName, AbstractAnimation* animation);
   virtual AbstractTexture* GetTexture(const string& textureName) {
      return _textures[textureName];
   }
   virtual AbstractAnimation* GetAnimation(const string& animationName) {
      return _animations[animationName];
   }
   virtual AbstractGraphicsShader* GetShader(const string& shaderName) {
      return _shaders[shaderName];
   }
   
   virtual bool InitializeContext() = 0;
   virtual void ShowWindow() = 0;
   virtual void Setup() = 0;
   virtual void Run() = 0;

protected:
   virtual void Init();
};

#endif

