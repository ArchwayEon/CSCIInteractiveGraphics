#pragma once
#ifndef BASE_GRAPHICS_SCENE
#define BASE_GRAPHICS_SCENE
#include <map>
#include <string>
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"
using std::map;
using std::string;

class AbstractGraphicsShader;
class AbstractAnimation;
class BaseCamera;
class AbstractGraphicsSystem;

class BaseGraphicsScene
{
protected:
   map<string, AbstractGraphicsObject*> _objects;
   size_t _numberOfLights;
   AbstractGraphicsSystem* _graphics;
   string _error;

public:
   static const int NumberOfLights = 10;
   Light globalLight;
   Light localLight[BaseGraphicsScene::NumberOfLights];
   BaseCamera* camera;

public:
   BaseGraphicsScene(AbstractGraphicsSystem* graphics, BaseCamera* camera);
   virtual ~BaseGraphicsScene();
   virtual void AddObject(
      const string& objectName, 
      AbstractGraphicsObject* object, 
      AbstractGraphicsShader* shader);
   virtual void RemoveObject(const string& objectName);
   virtual AbstractGraphicsObject* GetGraphicsObject(const string& objectName) {
      return _objects[objectName];
   }
   virtual void SetObjectsAnimation(const string& objectName, AbstractAnimation* animation);
   virtual void Setup();
   virtual void Update(double elapsedSeconds);
   virtual void Render();
   virtual size_t AddLight();
   const string& GetError() const { return _error; }
   void AddError(string error) { _error += error; }
   virtual bool LoadScene() { return true; }

protected:
   virtual void Init();
   virtual bool LoadShaders() { return true; };
   virtual bool LoadTextures() { return true; };
   virtual bool LoadAnimations() { return true; };
   virtual bool LoadObjects() { return true; };
   virtual bool LoadLights() { return true; };
};

#endif

