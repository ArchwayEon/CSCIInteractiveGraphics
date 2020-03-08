#pragma once
#ifndef OPENGL_TEXTURE
#define OPENGL_TEXTURE

#include "AbstractTexture.h"
#include <glad\glad.h>

class OpenGLTexture :
   public AbstractTexture
{
protected:
   GLuint _id;
   GLint _wrapS, _wrapT;
   GLint _minFilter, _magFilter;

public:
   OpenGLTexture();
   virtual ~OpenGLTexture();

   void SetWrapS(GLint wrapS) { _wrapS = wrapS; }
   void SetWrapT(GLint wrapT) { _wrapT = wrapT; }
   void SetMinFilter(GLint minFilter) { _minFilter = minFilter; }
   void SetMagFilter(GLint magFilter) { _magFilter = magFilter; }

   void LoadFromFile(const string& filename);
   void LoadFromArray(unsigned char* data, unsigned int size, int width, int height);
   void Select();
   void Setup();
};

#endif