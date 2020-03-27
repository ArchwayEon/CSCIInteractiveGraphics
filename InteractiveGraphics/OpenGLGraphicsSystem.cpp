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
}

void OpenGLGraphicsSystem::Setup()
{
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
   if (_window->GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingLeft);
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      _camera->SetState(BaseCamera::CameraState::MovingRight);
      return;
   }
   _camera->SetState(BaseCamera::CameraState::NotMoving);

   if (_window->GetKeyState(GLFW_KEY_Y) == GLFW_PRESS) {
      scene->localLight.position.y += 0.1f;
      auto cube = (OpenGLGraphicsObject * )scene->GetGraphicsObject("cube");
      cube->frame.Move({ 0, 0.1f, 0 });
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_H) == GLFW_PRESS) {
      scene->localLight.position.y -= 0.1f;
      auto cube = (OpenGLGraphicsObject*)scene->GetGraphicsObject("cube");
      cube->frame.Move({ 0, -0.1f, 0 });
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_G) == GLFW_PRESS) {
      scene->localLight.position.x -= 0.1f;
      auto cube = (OpenGLGraphicsObject*)scene->GetGraphicsObject("cube");
      cube->frame.Move({ -0.1f, 0, 0 });
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_K) == GLFW_PRESS) {
      scene->localLight.position.x += 0.1f;
      auto cube = (OpenGLGraphicsObject*)scene->GetGraphicsObject("cube");
      cube->frame.Move({ 0.1f, 0, 0 });
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_U) == GLFW_PRESS) {
      scene->localLight.position.z -= 0.1f;
      auto cube = (OpenGLGraphicsObject*)scene->GetGraphicsObject("cube");
      cube->frame.Move({ 0, 0, -0.1f });
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_J) == GLFW_PRESS) {
      scene->localLight.position.z += 0.1f;
      auto cube = (OpenGLGraphicsObject*)scene->GetGraphicsObject("cube");
      cube->frame.Move({ 0, 0, 0.1f });
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_1) == GLFW_PRESS) {
      scene->globalLight.intensity += 0.01f;
      if (scene->globalLight.intensity > 1) {
         scene->globalLight.intensity = 1;
      }
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_2) == GLFW_PRESS) {
      scene->globalLight.intensity -= 0.01f;
      if (scene->globalLight.intensity < 0) {
         scene->globalLight.intensity = 0;
      }
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_3) == GLFW_PRESS) {
      auto crate = (OpenGLGraphicsObject*)scene->GetGraphicsObject("crate2");
      crate->material.ambientIntensity += .01f;
      if (crate->material.ambientIntensity > 1)
         crate->material.ambientIntensity = 1;
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_4) == GLFW_PRESS) {
      auto crate = (OpenGLGraphicsObject*)scene->GetGraphicsObject("crate2");
      crate->material.ambientIntensity -= .01f;
      if (crate->material.ambientIntensity < 0)
         crate->material.ambientIntensity = 0;
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_5) == GLFW_PRESS) {
      if (scene->localLight.color.red == 1.0f &&
         scene->localLight.color.green == 1.0f &&
         scene->localLight.color.blue == 1.0f)
         scene->localLight.color = { 1.0f, 0.0f, 0.0f };
      else if (scene->localLight.color.red == 1.0f &&
         scene->localLight.color.green == 0.0f &&
         scene->localLight.color.blue == 0.0f)
         scene->localLight.color = { 0.0f, 1.0f, 0.0f };
      else if (scene->localLight.color.red == 0.0f &&
         scene->localLight.color.green == 1.0f &&
         scene->localLight.color.blue == 0.0f)
         scene->localLight.color = { 0.0f, 0.0f, 1.0f };
      else if (scene->localLight.color.red == 0.0f &&
         scene->localLight.color.green == 0.0f &&
         scene->localLight.color.blue == 1.0f)
         scene->localLight.color = { 1.0f, 1.0f, 1.0f };
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_6) == GLFW_PRESS) {
      scene->localLight.intensity += 0.01f;
      if (scene->localLight.intensity > 1) {
         scene->localLight.intensity = 1;
      }
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_7) == GLFW_PRESS) {
      scene->localLight.intensity -= 0.01f;
      if (scene->localLight.intensity < 0) {
         scene->localLight.intensity = 0;
      }
      return;
   }
   if (_window->GetKeyState(GLFW_KEY_8) == GLFW_PRESS) {
      scene->localLight.attenuationCoefficient += 0.1f;
      if (scene->localLight.attenuationCoefficient > 1) {
         scene->localLight.attenuationCoefficient = 1;
      }
      return;
   }

   if (_window->GetKeyState(GLFW_KEY_9) == GLFW_PRESS) {
      scene->localLight.attenuationCoefficient -= 0.1f;
      if (scene->localLight.attenuationCoefficient < 0) {
         scene->localLight.attenuationCoefficient = 0;
      }
      return;
   }

}


