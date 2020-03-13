#include "BaseGraphicsScene.h"
#include "AbstractGraphicsShader.h"
#include "AbstractAnimation.h"
#include "BaseCamera.h"

BaseGraphicsScene::BaseGraphicsScene(BaseCamera* camera)
{
   this->camera = camera;
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
   this->camera->frame.SetPosition(0.0f, 3.0f, 10.0f);
   this->globalLight.color = { 1.0f, 1.0f, 1.0f }; // White light
   this->globalLight.intensity = 0.25f;
   this->globalLight.position = { 100.0f, 100.0f, 0.0f };

   this->localLight.color = { 1, 1, 1 };
   this->localLight.intensity = 0.5f;
   this->localLight.position = { 4.0f, 3.0f, -4.0f };
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

void BaseGraphicsScene::SetObjectsAnimation(const string& objectName, AbstractAnimation* animation)
{
   auto object = _objects[objectName];
   object->animation = animation;
   animation->graphicsObject = object;
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
   glm::vec3 localLightPosition(
      this->localLight.position.x,
      this->localLight.position.y,
      this->localLight.position.z);
   glm::vec3 localLightColor(
      this->localLight.color.red,
      this->localLight.color.green,
      this->localLight.color.blue
   );
   for (auto iter = _objects.begin(); iter != _objects.end(); iter++) {
      auto shader = iter->second->GetShader();
      shader->Select();
      shader->SendGlobalLightToGPU(
         globalLightPosition, 
         globalLightColor, 
         this->globalLight.intensity);
      shader->SendLocalLightToGPU(
         localLightPosition,
         localLightColor,
         this->localLight.intensity);
      iter->second->Render();
   }
}


