#include "AbstractGraphicsSystem.h"

AbstractGraphicsSystem::~AbstractGraphicsSystem()
{
   if (_window != nullptr) {
      delete _window;
   }
   if (_object != nullptr) {
      delete _object;
   }
   if (_shader != nullptr) {
      delete _shader;
   }
}
