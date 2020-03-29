#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLGraphicsObject.h"
#include "OpenGLVertexPCTStrategy.h"

OpenGLGraphicsSystem::OpenGLGraphicsSystem() :
   AbstractGraphicsSystem()
{
   _window = new OpenGLGraphicsWindow("OpenGL Window", 800, 600);
}

OpenGLGraphicsSystem::OpenGLGraphicsSystem(
   OpenGLGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer) :
   AbstractGraphicsSystem(window, camera, timer)
{
}

OpenGLGraphicsSystem::~OpenGLGraphicsSystem()
{
   glfwTerminate();
}

bool OpenGLGraphicsSystem::InitializeContext()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   if (!_window->Create()) {
      glfwTerminate();
      return false;
   }
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      _errorReport = "Failed to initialize GLAD\n";
      return false;
   }
   bool shaderNotCreated = false;
   for (auto shaderIter = _shaders.begin(); shaderIter != _shaders.end(); shaderIter++) {
      auto shader = shaderIter->second;
      if (!shader->Create()) {
         _errorReport += shader->ReportErrors();
         shaderNotCreated = true;
      }
   }
   if (shaderNotCreated) return false;
   return true;
}

void OpenGLGraphicsSystem::ShowWindow()
{
   _window->SetOnResize();
   _window->ShowMaximized();
   _window->SetOnMouseEvent();
}

void OpenGLGraphicsSystem::Setup()
{
   _window->HideAndCaptureMouseCursor();

   // Cull back faces and use counter-clockwise winding of front faces
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);

   // Enable depth testing
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glDepthFunc(GL_LEQUAL);
   glDepthRange(0.0f, 1.0f);

   this->scene->Setup();
}

void OpenGLGraphicsSystem::Run()
{
   double elapsedSeconds;
   _timer->StartTiming();
   _window->GetWindowSize();
   _window->ResetMouse();
   while (!_window->IsTimeToClose()) {
      elapsedSeconds = _timer->GetElapsedTimeInSeconds();
      ProcessInput();
      
      _camera->SetupLookingForward();
      _camera->SetupProjectionAndView(_window->GetAspectRatio());

      for (auto shaderIter = _shaders.begin(); shaderIter != _shaders.end(); shaderIter++) {
         auto shader = (GLSLGraphicsShader*)shaderIter->second;
         shader->projection = _camera->GetProjection();
         shader->view = _camera->GetView();
      }
      
      _camera->Update(elapsedSeconds);
      _window->Clear();
      this->scene->Update(elapsedSeconds);
      this->scene->Render();
      _window->SwapBuffers();
   }
}

void OpenGLGraphicsSystem::ProcessInput()
{
   if (_window->GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      _window->Close();
      return;
   }
   _camera->frame.SetFromSphericalCoordinates(_window->spherical);
   if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingRight);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingLeft);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_W) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingForward);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_S) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingBackward);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingUp);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingDown);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingLeft);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingRight);
      return;
   }
   _camera->SetState(BaseCamera::CameraState::NotMoving);

}


