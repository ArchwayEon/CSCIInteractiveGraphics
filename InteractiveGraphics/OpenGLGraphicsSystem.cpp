#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLGraphicsObject.h"

OpenGLGraphicsSystem::OpenGLGraphicsSystem() :
   AbstractGraphicsSystem()
{
   _window = new OpenGLGraphicsWindow("OpenGL Window", 800, 600);
}

OpenGLGraphicsSystem::OpenGLGraphicsSystem(
   OpenGLGraphicsWindow* window, BaseCamera* camera, AbstractTimer* timer, GLSLGraphicsShader* shader) :
   AbstractGraphicsSystem(window, camera, timer, shader)
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
   if (_shader != nullptr) {
      if (!_shader->Create()) {
         _errorReport = _shader->ReportErrors();
         return false;
      }
   }
   else {
      _errorReport = "A shader was not created.\n";
      return false;
   }
   return true;
}

void OpenGLGraphicsSystem::ShowWindow()
{
   _window->SetOnResize();
   _window->ShowMaximized();
}

void OpenGLGraphicsSystem::Setup()
{
   glEnable(GL_DEPTH_TEST);
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Setup();
   }
}

void OpenGLGraphicsSystem::Run()
{
   double elapsedSeconds;
   auto shader = (GLSLGraphicsShader*)_shader;
   _timer->StartTiming();
   while (!_window->IsTimeToClose()) {
      elapsedSeconds = _timer->GetElapsedTimeInSeconds();
      ProcessInput();
      
      _camera->SetupLookingForward();
      _camera->SetupProjectionAndView(_window->GetAspectRatio());
      shader->projection = _camera->GetProjection();
      shader->view = _camera->GetView();
      
      _camera->Update(elapsedSeconds);
      _window->Clear();
      for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
         iterator->second->Render();
      }

      _window->SwapBuffers();
   }
}

void OpenGLGraphicsSystem::ProcessInput()
{
   if (_window->GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      _window->Close();
   }
   auto cube = (OpenGLGraphicsObject*)_objects["Cube"];
   auto c2 = (OpenGLGraphicsObject*)_objects["C2"];
   if (_window->GetKeyState(GLFW_KEY_Y) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(0, 1, 0));
      c2->frame.RotateWorld(1, glm::vec3(0, 1, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_X) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(1, 0, 0));
      c2->frame.RotateWorld(1, glm::vec3(1, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_Z) == GLFW_PRESS) {
      cube->frame.Rotate(1, glm::vec3(0, 0, 1));
      c2->frame.RotateWorld(1, glm::vec3(0, 0, 1));
   }
   if (_window->GetKeyState(GLFW_KEY_R) == GLFW_PRESS) {
      cube->frame.Reset();
      c2->frame.Reset();
   }
   if (_window->GetKeyState(GLFW_KEY_1) == GLFW_PRESS) {
      c2->frame.Scale(0.9f);
   }
   if (_window->GetKeyState(GLFW_KEY_2) == GLFW_PRESS) {
      c2->frame.Scale(1.1f);
   }

   if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS) {
      if (_window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
         _camera->SetState(BaseCamera::CameraState::MovingRight);
      }
      else {
         _camera->SetState(BaseCamera::CameraState::TurningRight);
      }
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS) {
      if (_window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
         _camera->SetState(BaseCamera::CameraState::MovingLeft);
      }
      else {
         _camera->SetState(BaseCamera::CameraState::TurningLeft);
      }
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
   _camera->SetState(BaseCamera::CameraState::NotMoving);

}


