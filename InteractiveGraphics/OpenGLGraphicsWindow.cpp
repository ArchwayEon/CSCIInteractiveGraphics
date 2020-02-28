#include "OpenGLGraphicsWindow.h"

bool OpenGLGraphicsWindow::Create()
{
   _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
   if (_window == NULL) {
      return false;
   }
   glfwMakeContextCurrent(_window);
   return true;
}

void OpenGLGraphicsWindow::SetOnResize()
{
   glfwSetFramebufferSizeCallback(_window, OpenGLGraphicsWindow::OnResize);
}

void OpenGLGraphicsWindow::Show()
{
   glfwShowWindow(_window);
}

void OpenGLGraphicsWindow::ShowMaximized()
{
   glfwMaximizeWindow(_window);
}

void OpenGLGraphicsWindow::Close()
{
   glfwSetWindowShouldClose(_window, true);
}

bool OpenGLGraphicsWindow::IsTimeToClose()
{
   return glfwWindowShouldClose(_window);
}

void OpenGLGraphicsWindow::SwapBuffers()
{
   glfwSwapBuffers(_window);
   glfwPollEvents();
}

void OpenGLGraphicsWindow::Clear()
{
   glClearColor(
      backgroundColor.red, 
      backgroundColor.green, 
      backgroundColor.blue, 
      backgroundColor.alpha);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

int OpenGLGraphicsWindow::GetKeyState(int key)
{
   return glfwGetKey(_window, key);
}

void OpenGLGraphicsWindow::GetWindowSize()
{
   glfwGetWindowSize(_window, &_width, &_height);
}

float OpenGLGraphicsWindow::GetAspectRatio()
{
   GetWindowSize();
   return _width / (float)_height;
}

void OpenGLGraphicsWindow::OnResize(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}
