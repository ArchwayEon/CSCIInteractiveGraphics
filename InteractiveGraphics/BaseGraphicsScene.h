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

class BaseGraphicsScene
{
protected:
   map<string, AbstractGraphicsObject*> _objects;
   size_t _numberOfLights;

public:
   static const int NumberOfLights = 10;
   Light globalLight;
   Light localLight[BaseGraphicsScene::NumberOfLights];
   BaseCamera* camera;

public:
   BaseGraphicsScene(BaseCamera* camera);
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

protected:
   virtual void Init();
};

#endif

