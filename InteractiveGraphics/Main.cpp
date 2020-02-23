#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"

void ReportError(const string& error) 
{
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
      new OpenGLGraphicsWindow("Interactive Graphics Lec Week 6");
   window->backgroundColor = { 0.5f, 0.0f, 0.5f };

   OpenGLGraphicsObject* rectangle = new OpenGLGraphicsObject();
   Vertex* rectangleVertices = new Vertex[6];
   rectangleVertices[0].x = -0.5f;
   rectangleVertices[0].y =  0.5f;
   rectangleVertices[0].z =  0.0f;
   rectangleVertices[0].red = 1.0f;
   rectangleVertices[0].green = 0.0f;
   rectangleVertices[0].blue = 0.0f;

   rectangleVertices[1].x = -0.5f;
   rectangleVertices[1].y = -0.5f;
   rectangleVertices[1].z =  0.0f;
   rectangleVertices[1].red = 1.0f;
   rectangleVertices[1].green = 0.0f;
   rectangleVertices[1].blue = 0.0f;

   rectangleVertices[2].x =  0.5f;
   rectangleVertices[2].y = -0.5f;
   rectangleVertices[2].z =  0.0f;
   rectangleVertices[2].red = 1.0f;
   rectangleVertices[2].green = 0.0f;
   rectangleVertices[2].blue = 0.0f;

   rectangleVertices[3].x = -0.5f;
   rectangleVertices[3].y = 0.5f;
   rectangleVertices[3].z = 0.0f;
   rectangleVertices[3].red = 0.0f;
   rectangleVertices[3].green = 0.0f;
   rectangleVertices[3].blue = 1.0f;

   rectangleVertices[4].x = 0.5f;
   rectangleVertices[4].y = -0.5f;
   rectangleVertices[4].z = 0.0f;
   rectangleVertices[4].red = 0.0f;
   rectangleVertices[4].green = 0.0f;
   rectangleVertices[4].blue = 1.0f;

   rectangleVertices[5].x = 0.5f;
   rectangleVertices[5].y = 0.5f;
   rectangleVertices[5].z = 0.0f;
   rectangleVertices[5].red = 0.0f;
   rectangleVertices[5].green = 0.0f;
   rectangleVertices[5].blue = 1.0f;

   rectangle->SetObjectData(rectangleVertices, 6);

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