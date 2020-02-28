#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLGraphicsObject.h"

OpenGLGraphicsSystem::OpenGLGraphicsSystem() : 
   AbstractGraphicsSystem(), _cameraPos({ 0.0f, 3.0f, 10.0f })
{
   _window = new OpenGLGraphicsWindow("OpenGL Window", 800, 600);
}

OpenGLGraphicsSystem::OpenGLGraphicsSystem(
   OpenGLGraphicsWindow* window, GLSLGraphicsShader* shader):
   AbstractGraphicsSystem(window, shader), _cameraPos({ 0.0f, 3.0f, 10.0f })
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
   auto shader = (GLSLGraphicsShader*)_shader;
   while (!_window->IsTimeToClose()) {
      ProcessInput();

      _aspectRatio = _window->GetAspectRatio();
      shader->projection = 
         glm::perspective(
            glm::radians(60.0f), // FOV
            _aspectRatio,
            0.1f,  // Near view plane
            100.0f // Far view plane
         );
      shader->view = glm::lookAt(
         glm::vec3(_cameraPos.x, _cameraPos.y, _cameraPos.z), // Position
         glm::vec3(0.0f, 0.0f, 0.0f),  // Target
         glm::vec3(0.0f, 1.0f, 0.0f)   // Up
      );
 
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
   if (_window->GetKeyState(GLFW_KEY_Y) == GLFW_PRESS) {
      _objects["Cube"]->Rotate(1, glm::vec3(0, 1, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_X) == GLFW_PRESS) {
      _objects["Cube"]->Rotate(1, glm::vec3(1, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_Z) == GLFW_PRESS) {
      _objects["Cube"]->Rotate(1, glm::vec3(0, 0, 1));
   }
   if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS) {
      _objects["Cube"]->Move(glm::vec3(0.1f, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS) {
      _objects["Cube"]->Move(glm::vec3(-0.1f, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_W) == GLFW_PRESS) {
      _objects["Cube"]->Move(glm::vec3(0, 0.1f, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_S) == GLFW_PRESS) {
      _objects["Cube"]->Move(glm::vec3(0, -0.1f, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_R) == GLFW_PRESS) {
      ((OpenGLGraphicsObject*)_objects["Cube"])->orientation = glm::mat4(1.0);
   }

   if (_window->GetKeyState(GLFW_KEY_1) == GLFW_PRESS) {
      _cameraPos = { 0.0f, 3.0f, 10.0f };
   }
   if (_window->GetKeyState(GLFW_KEY_2) == GLFW_PRESS) {
      _cameraPos = { 0.0f, -3.0f, 10.0f };
   }

}


