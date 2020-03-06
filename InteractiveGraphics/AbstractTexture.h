#pragma once

#ifndef ABSTRACT_TEXTURE
#define ABSTRACT_TEXTURE
#include <string>
using std::string;

class AbstractTexture
{
protected:
   int _width, _height;
   unsigned char* _data;
   bool _loadedFromFile;
   string _error;

public:
   AbstractTexture() : _width(0), _height(0), _data(nullptr), _loadedFromFile(false) {}
   virtual ~AbstractTexture();

   virtual void LoadFromFile(const string& filename) = 0;
   virtual void SetTextureData(unsigned char* data, unsigned int size, int width, int height) = 0;
   virtual void Select() = 0;
   virtual void Setup() = 0;
   string ErrorReport() { return _error; }
};

#endif
