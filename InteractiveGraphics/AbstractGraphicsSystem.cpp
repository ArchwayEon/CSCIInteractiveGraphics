#include "AbstractGraphicsSystem.h"
#include "BaseGraphicsScene.h"


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
   this->scene = nullptr;
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
   for (auto animationIter = this->_animations.begin();
      animationIter != this->_animations.end(); animationIter++) {
      delete animationIter->second;
   }
   this->_animations.clear();
   if (this->scene != nullptr) {
      delete this->scene;
   }
}

void AbstractGraphicsSystem::AddShader(const string& shaderName, AbstractGraphicsShader* shader)
{
   _shaders[shaderName] = shader;
}

void AbstractGraphicsSystem::AddTexture(const string& textureName, AbstractTexture* texture)
{
   _textures[textureName] = texture;
}

void AbstractGraphicsSystem::AddAnimation(const string& animationName, AbstractAnimation* animation)
{
   _animations[animationName] = animation;
}




