#pragma once
#ifndef OPENGL_GRAPHICS_SYSTEM
#define OPENGL_GRAPHICS_SYSTEM

#include "AbstractGraphicsSystem.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "OpenGLGraphicsWindow.h"

class OpenGLGraphicsSystem :
   public AbstractGraphicsSystem
{
private:
   GLuint _shaderProgram;

private:
   void ProcessInput();
   bool SetupShaders();
   GLuint CompileShader(GLenum type, const GLchar* source);
   GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);

public:
   OpenGLGraphicsSystem();
   OpenGLGraphicsSystem(OpenGLGraphicsWindow* window);
   ~OpenGLGraphicsSystem();
   bool InitializeContext();
   void ShowWindow();
   void Setup();
   void Run();
};

#endif

