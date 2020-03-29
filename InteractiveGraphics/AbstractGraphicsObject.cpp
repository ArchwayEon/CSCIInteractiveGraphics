#include "AbstractGraphicsObject.h"
#include "AbstractAnimation.h"

AbstractGraphicsObject::AbstractGraphicsObject() :
   _shader(nullptr), _texture(nullptr), vertexStrategy(nullptr),
   frame(), animation(nullptr)
{
   Init();
}

AbstractGraphicsObject::AbstractGraphicsObject(AbstractGraphicsShader* shader, AbstractTexture* texture) :
   _shader(shader), vertexStrategy(nullptr), _texture(nullptr), frame(), animation(nullptr)
{
   Init();
}

void AbstractGraphicsObject::Init()
{
   material.ambientIntensity = 0.01f;
   material.specularIntensity = 0.5f;
   material.shininess = 16;
}

AbstractGraphicsObject::~AbstractGraphicsObject()
{
   if (this->vertexStrategy != nullptr) {
      delete this->vertexStrategy;
   }
}

void AbstractGraphicsObject::Update(double elapsedSeconds)
{
   if (this->animation != nullptr) {
      this->animation->Update(elapsedSeconds);
   }
}


