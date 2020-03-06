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
   for (auto iterator = this->_objects.begin(); iterator != this->_objects.end(); iterator++) {
      delete iterator->second;
   }
   this->_objects.clear();
   if (_shader != nullptr) {
      delete _shader;
   }
}
