#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"
#include "GraphicsObjectReader.h"

void ReportError(const string& error) 
{
   // Quick way to convert from string to wstring
   wstring errorString(error.begin(), error.end());
   MessageBox(
      NULL,
      errorString.c_str(),
      L"An Error Occurred",
      MB_OK);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   OpenGLGraphicsWindow* window = 
      new OpenGLGraphicsWindow("Interactive Graphics Lec Week 7");
   //window->backgroundColor = { 0.5f, 0.0f, 0.5f };

   OpenGLGraphicsObject* object = nullptr;
   GraphicsObjectReader reader("cube.ig");
   if (reader.Read()) {
      object = reader.GetObject();
   }
   else {
      ReportError(reader.ReportErrors());
      return 0;
   }

   GLSLGraphicsShader* shader = 
      new GLSLGraphicsShader(new TextFileReader());
   if (!shader->ReadShaderSources(
      "Simple3DVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(shader->ReportErrors());
      return 0;
   }
   object->SetShader(shader);

   auto camera = new BaseCamera();
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, shader);

   graphics->AddObject("Cube", object);

   if (graphics->InitializeContext()) {
      graphics->ShowWindow();
      graphics->Setup();
      graphics->Run();
   }
   else {
      ReportError(graphics->ReportErrors());
   }
   delete graphics;
   return 0;
}