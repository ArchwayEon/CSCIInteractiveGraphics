#include "AbstractGraphicsObject.h"

AbstractGraphicsObject::~AbstractGraphicsObject()
{
   if (this->vertexStrategy != nullptr) {
      delete this->vertexStrategy;
   }
}
