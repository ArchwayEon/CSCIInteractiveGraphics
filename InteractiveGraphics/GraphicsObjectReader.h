#pragma once
#ifndef GRAPHICS_OBJECT_READER
#define GRAPHICS_OBJECT_READER

#include "AbstractReader.h"
#include "OpenGLGraphicsObject.h"
class GraphicsObjectReader :
   public AbstractReader
{
private:
   OpenGLGraphicsObject* _object;
   string _filePath;

public:
   GraphicsObjectReader(string filePath) : 
      _filePath(filePath), _object(nullptr) {}
   OpenGLGraphicsObject* GetObject() { return _object; }
   bool Read();
};

#endif

