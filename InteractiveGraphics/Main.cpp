#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"
#include "GraphicsObjectReader.h"
#include "Generate.h"
#include "HighResolutionTimer.h"

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

   auto timer = new HighResolutionTimer();
   auto camera = new BaseCamera();
   camera->frame.SetPosition(2.0f, 1.0f, 7.0f);
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, timer, shader);

   graphics->AddObject("Cube", object);
   object = Generate::IndexedFlatSurface(10, 10, { 0.0f, 0.0f, 0.5f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("Floor", object);

   auto cube = (OpenGLGraphicsObject*)graphics->GetObject("Cube");
   cube->frame.Move({ 0.0f, 0.5f, 0.0f });

   object = Generate::Cuboid(0.5f, 1, 1, { 0.5f, 0.5f, 0.0f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("C2", object);
   object->frame.Move({ 3.0f, 0.5f, 0.0f });
   auto c2 = (OpenGLGraphicsObject*)graphics->GetObject("C2");
   c2->SetColor(0, 6, { 0.5f, 0.0f, 0.0f, 1.0f });

   object = Generate::Cuboid(1, 2, 1, { 0.0f, 0.5f, 0.5f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("C3", object);
   object->frame.Move({ 0.0f, 0.5f, 4.0f });
   auto c3 = (OpenGLGraphicsObject*)graphics->GetObject("C3");
   c3->SetColor(5, 6, { 0.0f, 0.0f, 0.5f, 1.0f });

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