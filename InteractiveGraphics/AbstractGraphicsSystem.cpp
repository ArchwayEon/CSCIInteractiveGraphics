#include "AbstractGraphicsSystem.h"

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
   for (auto objectIter = this->_objects.begin(); objectIter != this->_objects.end(); objectIter++) {
      delete objectIter->second;
   }
   this->_objects.clear();
   for (auto shaderIter = this->_shaders.begin(); shaderIter != this->_shaders.end(); shaderIter++) {
      delete shaderIter->second;
   }
   this->_shaders.clear();
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
