#include "BaseGraphicsScene.h"
#include "AbstractGraphicsShader.h"

BaseGraphicsScene::BaseGraphicsScene()
{
   Init();
}

BaseGraphicsScene::~BaseGraphicsScene()
{
   for (auto objectIter = this->_objects.begin();
      objectIter != this->_objects.end(); objectIter++) {
      delete objectIter->second;
   }
   this->_objects.clear();
}

void BaseGraphicsScene::Init()
{
   this->globalLight.color = { 1.0f, 1.0f, 1.0f }; // White light
   this->globalLight.intensity = 0.25f;
   this->globalLight.position = { 100.0f, 100.0f, 0.0f };
}

void BaseGraphicsScene::AddObject(
   const string& objectName, AbstractGraphicsObject* object, AbstractGraphicsShader* shader)
{
   _objects[objectName] = object;
   _objects[objectName]->SetShader(shader);
}

void BaseGraphicsScene::RemoveObject(const string& objectName)
{
   auto objectIter = _objects.find(objectName);
   if (objectIter != _objects.end()) {
      delete objectIter->second;
      _objects.erase(objectIter);
   }
}

void BaseGraphicsScene::Setup()
{
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Setup();
   }
}

void BaseGraphicsScene::Update(double elapsedSeconds)
{
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Update(elapsedSeconds);
   }
}

void BaseGraphicsScene::Render()
{
   glm::vec3 globalLightPosition(
      this->globalLight.position.x,
      this->globalLight.position.y,
      this->globalLight.position.z);
   glm::vec3 globalLightColor(
      this->globalLight.color.red,
      this->globalLight.color.green,
      this->globalLight.color.blue
   );
   for (auto iter = _objects.begin(); iter != _objects.end(); iter++) {
      auto shader = iter->second->GetShader();
      shader->Select();
      shader->SendGlobalLightToGPU(
         globalLightPosition, 
         globalLightColor, 
         this->globalLight.intensity);
      iter->second->Render();
   }
}


