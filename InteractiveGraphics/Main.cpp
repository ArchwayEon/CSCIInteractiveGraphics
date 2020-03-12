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
#include "OpenGLTexture.h"
#include "RotateAnimation.h"

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
      new OpenGLGraphicsWindow("Interactive Graphics Lec Week 10");

   // Load the shaders
   GLSLGraphicsShader* simple3DShader = new GLSLGraphicsShader(new TextFileReader());
   if (!simple3DShader->ReadShaderSources(
      "Simple3DVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(simple3DShader->ReportErrors());
      return 0;
   }
   GLSLGraphicsShader* simplePCTShader = new GLSLGraphicsShader(new TextFileReader());
   if (!simplePCTShader->ReadShaderSources(
      "VSPositionColorTexture.glsl", "FSPositionColorTexture.glsl")) {
      ReportError(simplePCTShader->ReportErrors());
      return 0;
   }
   GLSLGraphicsShader* ambientLightShader = new GLSLGraphicsShader(new TextFileReader());
   if (!ambientLightShader->ReadShaderSources(
      "VSPositionColorTexture.glsl", "FSPCTAmbientLight.glsl")) {
      ReportError(ambientLightShader->ReportErrors());
      return 0;
   }

   GLSLGraphicsShader* globalLightShader = new GLSLGraphicsShader(new TextFileReader());
   if (!globalLightShader->ReadShaderSources(
      "VSPCNTLighting.glsl", "FSPCNTLight.glsl")) {
      ReportError(globalLightShader->ReportErrors());
      return 0;
   }

   auto timer = new HighResolutionTimer();
   auto camera = new BaseCamera();
   camera->frame.SetPosition(2.0f, 3.0f, 10.0f);
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, timer);
   graphics->AddShader("Simple3DShader", simple3DShader);
   graphics->AddShader("SimplePCTShader", simplePCTShader);
   graphics->AddShader("AmbientLightShader", ambientLightShader);
   graphics->AddShader("GlobalLightShader", globalLightShader);

   OpenGLTexture* wallTexture = new OpenGLTexture();
   wallTexture->LoadFromFile("brickwall.jpg");
   wallTexture->SetMagFilter(GL_LINEAR);
   wallTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("brickwall", wallTexture);

   OpenGLGraphicsObject* wall = Generate::NormalizedTexturedFlatSurface(10, 10, { 1.0f, 1.0f, 1.0f, 1.0f }, 5.0f, 5.0f);
   wall->SetTexture(wallTexture);
   graphics->AddObject("wall", wall, "GlobalLightShader");
   wall->frame.Move({ 0.0f, 5.0f, -5.0f });
   wall->frame.Rotate(90.0f, wall->frame.GetXAxis());

   OpenGLTexture* crateTexture = new OpenGLTexture();
   crateTexture->LoadFromFile("crate.jpg");
   graphics->AddTexture("crate", crateTexture);

   OpenGLGraphicsObject* crate1 = Generate::TexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate1->SetTexture(crateTexture);
   graphics->AddObject("crate1", crate1, "AmbientLightShader");
   crate1->frame.Move({ -3.0f, 1.0f, 0.0f });

   OpenGLGraphicsObject* crate2 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate2->SetTexture(crateTexture);
   graphics->AddObject("crate2", crate2, "GlobalLightShader");
   crate2->frame.Move({ 0.0f, 1.0f, 0.0f });

   OpenGLGraphicsObject* crate3 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate3->SetTexture(crateTexture);
   graphics->AddObject("crate3", crate3, "GlobalLightShader");
   crate3->frame.Move({ 3.0f, 1.0f, 0.0f });

   auto rotateAnimation = new RotateAnimation();
   rotateAnimation->graphicsObject = graphics->GetGraphicsObject("crate1");
   graphics->GetGraphicsObject("crate1")->animation = rotateAnimation;

   rotateAnimation = new RotateAnimation();
   rotateAnimation->graphicsObject = graphics->GetGraphicsObject("crate2");
   graphics->GetGraphicsObject("crate2")->animation = rotateAnimation;

   rotateAnimation = new RotateAnimation();
   rotateAnimation->graphicsObject = graphics->GetGraphicsObject("crate3");
   graphics->GetGraphicsObject("crate3")->animation = rotateAnimation;

   OpenGLTexture* floorTexture = new OpenGLTexture();
   floorTexture->LoadFromFile("marble-stone-floor.jpg");
   floorTexture->SetMagFilter(GL_LINEAR);
   floorTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("marbleFloor", floorTexture);

   OpenGLGraphicsObject* floor = Generate::NormalizedTexturedFlatSurface(50, 50, { 1.0f, 1.0f, 1.0f, 1.0f }, 50.0f, 50.0f);
   floor->SetTexture(floorTexture);
   graphics->AddObject("floor", floor, "GlobalLightShader");

   OpenGLTexture* skyTexture = new OpenGLTexture();
   skyTexture->LoadFromFile("sky.jpg");
   skyTexture->SetMagFilter(GL_LINEAR);
   skyTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("sky", skyTexture);

   OpenGLGraphicsObject* sky = Generate::TexturedFlatSurface(100, 100, { 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1);
   sky->SetTexture(skyTexture);
   graphics->AddObject("sky", sky, "SimplePCTShader");
   sky->frame.Move({ 0.0f, 15.0f, 0.0f });
   sky->frame.Rotate(180.0f, wall->frame.GetXAxis());

   OpenGLGraphicsObject* cube = Generate::Cuboid(0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   graphics->AddObject("cube", cube, "Simple3DShader");
   cube->frame.Move({ -3.0f, 7.0f, -3.0f });

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