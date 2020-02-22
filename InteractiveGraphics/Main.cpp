#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   OpenGLGraphicsWindow* window = 
      new OpenGLGraphicsWindow("Interactive Graphics Lab Week 5", 800, 600);
   window->backgroundColor = { 0.5f, 0.0f, 0.5f };

   //OpenGLGraphicsObject* triangle = new OpenGLGraphicsObject();
   //Vertex* triangleVertices = new Vertex[3];
   //triangleVertices[0].x = 0.0f;
   //triangleVertices[0].y = 0.5f;
   //triangleVertices[0].z = 0.0f;
   //triangleVertices[0].red = 1.0f;
   //triangleVertices[0].green = 0.0f;
   //triangleVertices[0].blue = 0.0f;
   //
   //triangleVertices[1].x = -0.5f;
   //triangleVertices[1].y = -0.5f;
   //triangleVertices[1].z = 0.0f;
   //triangleVertices[1].red = 0.0f;
   //triangleVertices[1].green = 0.0f;
   //triangleVertices[1].blue = 1.0f;
   //
   //triangleVertices[2].x = 0.5f;
   //triangleVertices[2].y = -0.5f;
   //triangleVertices[2].z = 0.0f;
   //triangleVertices[2].red = 0.0f;
   //triangleVertices[2].green = 1.0f;
   //triangleVertices[2].blue = 0.0f;
   //triangle->SetObjectData(triangleVertices, 3);

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

   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window);
   graphics->SetObject(rectangle);

   graphics->InitializeContext();
   graphics->ShowWindow();
   graphics->Setup();
   graphics->Run();
   delete graphics;
   return 0;
}