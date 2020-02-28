#pragma once
#ifndef OPENGL_GRAPHICS_SYSTEM
#define OPENGL_GRAPHICS_SYSTEM
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "AbstractGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

class OpenGLGraphicsSystem :
   public AbstractGraphicsSystem
{
private:
   Vector _cameraPos;

private:
   void ProcessInput();

public:
   OpenGLGraphicsSystem();
   OpenGLGraphicsSystem(OpenGLGraphicsWindow* window, GLSLGraphicsShader* shader);
   ~OpenGLGraphicsSystem();
   bool InitializeContext();
   void ShowWindow();
   void Setup();
   void Run();
};

#endif

