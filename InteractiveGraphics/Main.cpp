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
      new OpenGLGraphicsWindow("Interactive Graphics Lab Week 6");
   window->backgroundColor = { 0.5f, 0.0f, 0.5f };

   OpenGLGraphicsObject* rectangle = nullptr;
   GraphicsObjectReader reader("rectangle.ig");
   if (reader.Read()) {
      rectangle = reader.GetObject();
   }
   else {
      ReportError(reader.ReportErrors());
      return 0;
   }

   GLSLGraphicsShader* shader = 
      new GLSLGraphicsShader(new TextFileReader());
   if (!shader->ReadShaderSources(
      "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(shader->ReportErrors());
      return 0;
   }
   rectangle->SetShader(shader);

   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, shader);
   graphics->SetObject(rectangle);
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