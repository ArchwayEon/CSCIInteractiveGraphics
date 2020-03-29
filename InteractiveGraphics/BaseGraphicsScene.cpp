#include "BaseGraphicsScene.h"
#include "AbstractGraphicsShader.h"
#include "AbstractAnimation.h"
#include "BaseCamera.h"

BaseGraphicsScene::BaseGraphicsScene(AbstractGraphicsSystem* graphics, BaseCamera* camera)
{
   this->_graphics = graphics;
   this->camera = camera;
   _error = "";
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
   this->_numberOfLights = 0;
   // Defaults to 1 light
   this->AddLight();
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
   glm::vec3 *localLightPositions = new glm::vec3[this->_numberOfLights];
   glm::vec3 *localLightColors = new glm::vec3[this->_numberOfLights];
   float *localLightIntensities = new float[this->_numberOfLights];
   float *localLightAttentuation = new float[this->_numberOfLights];
   for (int i = 0; i < this->_numberOfLights; i++) {
      localLightPositions[i].x = this->localLight[i].position.x;
      localLightPositions[i].y = this->localLight[i].position.y;
      localLightPositions[i].z = this->localLight[i].position.z;
      localLightColors[i].r = this->localLight[i].color.red;
      localLightColors[i].g = this->localLight[i].color.green;
      localLightColors[i].b = this->localLight[i].color.blue;
      localLightIntensities[i] = this->localLight[i].intensity;
      localLightAttentuation[i] = this->localLight[i].attenuationCoefficient;
   }
   for (auto iter = _objects.begin(); iter != _objects.end(); iter++) {
      auto shader = iter->second->GetShader();
      shader->Select();
      shader->SendGlobalLightToGPU(
         globalLightPosition, 
         globalLightColor, 
         this->globalLight.intensity);
      shader->SendLocalLightDataToGPU(
         this->_numberOfLights,
         localLightPositions,
         localLightColors,
         localLightIntensities,
         localLightAttentuation);
      shader->SendVector3ToGPU("viewPosition", camera->frame.GetPosition());
      iter->second->Render();
   }
   delete[] localLightPositions;
   delete[] localLightColors;
   delete[] localLightIntensities;
   delete[] localLightAttentuation;
}

size_t BaseGraphicsScene::AddLight()
{
   this->_numberOfLights++;
   size_t index = _numberOfLights - 1;
   this->localLight[index].color = { 1, 1, 1 };
   this->localLight[index].intensity = 0.5f;
   this->localLight[index].position = { 0.0f, 0.0f, 0.0f };
   this->localLight[index].attenuationCoefficient = 0.2f;
   return index;
}


