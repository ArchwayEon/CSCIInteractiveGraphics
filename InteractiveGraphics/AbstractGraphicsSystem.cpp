#include "AbstractGraphicsSystem.h"

AbstractGraphicsSystem::AbstractGraphicsSystem() : 
   _window(nullptr), _camera(new BaseCamera()), _timer(nullptr), _errorReport("")
{
   Init();
}

AbstractGraphicsSystem::AbstractGraphicsSystem(AbstractGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer) :
   _window(window), _camera(camera), _timer(timer), _errorReport("")
{
   Init();
}

void AbstractGraphicsSystem::Init()
{
   globalLight.color = { 1.0f, 1.0f, 1.0f }; // White light
   globalLight.intensity = 0.25f;
   globalLight.position = { 100.0f, 100.0f, 0.0f };
}

AbstractGraphicsSystem::~AbstractGraphicsSystem()
{
   if (_window != nullptr) {
      delete _window;
   }
   if (_camera != nullptr) {
      delete _camera;
   }
   if (_timer != nullptr) {
      delete _timer;
   }
   for (auto objectIter = this->_objects.begin(); 
      objectIter != this->_objects.end(); objectIter++) {
      delete objectIter->second;
   }
   this->_objects.clear();
   for (auto shaderIter = this->_shaders.begin(); 
      shaderIter != this->_shaders.end(); shaderIter++) {
      delete shaderIter->second;
   }
   this->_shaders.clear();

   for (auto textureIter = this->_textures.begin(); 
      textureIter != this->_textures.end(); textureIter++) {
      delete textureIter->second;
   }
   this->_textures.clear();
}

void AbstractGraphicsSystem::AddObject(const string& objectName, AbstractGraphicsObject* object, const string& shaderName)
{
   _objects[objectName] = object;
   _objects[objectName]->SetShader(_shaders[shaderName]);
}

void AbstractGraphicsSystem::RemoveObject(const string& objectName)
{
   auto objectIter = _objects.find(objectName);
   if (objectIter != _objects.end()) {
      _objects.erase(objectIter);
   }
}

void AbstractGraphicsSystem::AddShader(string shaderName, AbstractGraphicsShader* shader)
{
   _shaders[shaderName] = shader;
}

void AbstractGraphicsSystem::AddTexture(string textureName, AbstractTexture* texture)
{
   _textures[textureName] = texture;
}


