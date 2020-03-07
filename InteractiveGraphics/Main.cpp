#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"
#include "GraphicsObjectReader.h"
#include "Generate.h"
#include "HighResolutionTimer.h"
#include "OpenGLVertexPCStrategy.h"

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
      new OpenGLGraphicsWindow("Interactive Graphics Lec Week 8");

   OpenGLGraphicsObject* object = nullptr;
   GraphicsObjectReader reader("cube.ig");
   if (reader.Read()) {
      object = reader.GetGraphicsObject();
   }
   else {
      ReportError(reader.ReportErrors());
      return 0;
   }
   
   GLSLGraphicsShader* shader = new GLSLGraphicsShader(new TextFileReader());
   if (!shader->ReadShaderSources(
      "Simple3DVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(shader->ReportErrors());
      return 0;
   }

   auto timer = new HighResolutionTimer();
   auto camera = new BaseCamera();
   camera->frame.SetPosition(2.0f, 1.0f, 7.0f);
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, timer);
   graphics->AddShader("Simple3DShader", shader);

   graphics->AddObject("Cube", object, "Simple3DShader");

   object = Generate::IndexedFlatSurface(10, 10, { 0.5f, 0.5f, 0.5f, 1.0f });
   graphics->AddObject("Floor", object, "Simple3DShader");

   auto cube = (OpenGLGraphicsObject*)graphics->GetGraphicsObject("Cube");
   cube->frame.Move({ 0.0f, 0.5f, 0.0f });

   object = Generate::Cuboid(0.5f, 1, 1, { 0.5f, 0.5f, 0.0f, 1.0f });
   graphics->AddObject("C2", object, "Simple3DShader");
   object->frame.Move({ 3.0f, 0.5f, 0.0f });
   auto c2 = (OpenGLGraphicsObject*)graphics->GetGraphicsObject("C2");
   auto vertexStrategy = (OpenGLVertexPCStrategy*)c2->vertexStrategy;
   vertexStrategy->SetColor(0, 6, { 0.5f, 0.0f, 0.0f, 1.0f });

   object = Generate::Cuboid(1, 2, 1, { 0.0f, 0.5f, 0.5f, 1.0f });
   graphics->AddObject("C3", object, "Simple3DShader");
   object->frame.Move({ 0.0f, 0.5f, 4.0f });
   auto c3 = (OpenGLGraphicsObject*)graphics->GetGraphicsObject("C3");
   vertexStrategy = (OpenGLVertexPCStrategy*)c3->vertexStrategy;
   vertexStrategy->SetColor(0, 6, { 0.5f, 0.0f, 0.0f, 1.0f });

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