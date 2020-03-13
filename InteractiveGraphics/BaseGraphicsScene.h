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

class BaseGraphicsScene
{
protected:
   map<string, AbstractGraphicsObject*> _objects;

public:
   Light globalLight;

public:
   BaseGraphicsScene();
   virtual ~BaseGraphicsScene();
   virtual void AddObject(
      const string& objectName, 
      AbstractGraphicsObject* object, 
      AbstractGraphicsShader* shader);
   virtual void RemoveObject(const string& objectName);
   virtual AbstractGraphicsObject* GetGraphicsObject(const string& objectName) {
      return _objects[objectName];
   }
   virtual void Setup();
   virtual void Update(double elapsedSeconds);
   virtual void Render();

protected:
   virtual void Init();
};

#endif

