#pragma once
#ifndef OPENGL_GRAPHICS_WINDOW
#define OPENGL_GRAPHICS_WINDOW

#include <GLFW\glfw3.h>
#include "AbstractGraphicsWindow.h"

class OpenGLGraphicsWindow :
   public AbstractGraphicsWindow
{
private:
   GLFWwindow* _window;

public:
   OpenGLGraphicsWindow(string title, int width=800, int height=600) :
      AbstractGraphicsWindow(title, width, height) {
      backgroundColor.red = 0.0f;
      backgroundColor.green = 0.0f;
      backgroundColor.blue = 0.0f;
      backgroundColor.alpha = 1.0f;
      _window = nullptr;
   }
   bool Create();
   void SetOnResize();
   void Show();
   void ShowMaximized();
   void Close();
   bool IsTimeToClose();
   void SwapBuffers();
   void Clear();
   int GetKeyState(int key);
   void GetWindowSize();
   float GetAspectRatio();

private:
   static void OnResize(GLFWwindow* window, int width, int height);
};

#endif

