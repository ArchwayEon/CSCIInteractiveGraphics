#include "OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

OpenGLTexture::OpenGLTexture() : 
   AbstractTexture(), _id(0)
{
   _wrapS = _wrapT = GL_REPEAT;
   _minFilter = _magFilter = GL_NEAREST;
}

OpenGLTexture::~OpenGLTexture()
{
}

void OpenGLTexture::LoadFromFile(const string& filename)
{
   // https://github.com/nothings/stb
   int width, height, nrChannels;
   stbi_set_flip_vertically_on_load(true);
   _data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
   if (_data) {
      _width = width;
      _height = height;
      _loadedFromFile = true;
   }
   else {
      _error = "Could not load texture: " + filename;
   }
}

void OpenGLTexture::LoadFromArray(unsigned char* data, unsigned int size, int width, int height)
{
   _width = width;
   _height = height;
   _data = new unsigned char[size];
   for (unsigned int i = 0; i < size; i++) {
      _data[i] = data[i];
   }
   _loadedFromFile = false;
}

void OpenGLTexture::Select()
{
   glBindTexture(GL_TEXTURE_2D, _id);
}

void OpenGLTexture::Setup()
{
   if (_data != nullptr) {
      glGenTextures(1, &_id);
      glBindTexture(GL_TEXTURE_2D, _id);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
      glGenerateMipmap(GL_TEXTURE_2D);
      if (_loadedFromFile) {
         stbi_image_free(_data);
      }
      else {
         delete[] _data;
      }
      _data = nullptr;
   }
}
