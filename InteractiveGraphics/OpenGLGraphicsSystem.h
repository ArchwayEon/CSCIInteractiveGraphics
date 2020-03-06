#pragma once
#ifndef OPENGL_GRAPHICS_SYSTEM
#define OPENGL_GRAPHICS_SYSTEM
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "AbstractGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"
#include "AbstractTimer.h"

class OpenGLGraphicsSystem :
   public AbstractGraphicsSystem
{
public:
   OpenGLGraphicsSystem();
   OpenGLGraphicsSystem(
      OpenGLGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer, GLSLGraphicsShader* shader);
   ~OpenGLGraphicsSystem();
   bool InitializeContext();
   void ShowWindow();
   void Setup();
   void Run();

private:
   void ProcessInput();
};

#endif

