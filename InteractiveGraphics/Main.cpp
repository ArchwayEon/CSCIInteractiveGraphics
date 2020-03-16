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
#include "BaseGraphicsScene.h"

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
   auto timer = new HighResolutionTimer();
   auto camera = new BaseCamera();
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, timer);
   graphics->scene = new BaseGraphicsScene(camera);
   graphics->scene->globalLight.intensity = 0.05f;
   graphics->scene->localLight.color = { 1, 1, 1 };
   graphics->scene->localLight.intensity = 0.7f;

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
   GLSLGraphicsShader* localLightShader = new GLSLGraphicsShader(new TextFileReader());
   if (!localLightShader->ReadShaderSources(
      "VSPCNTLighting.glsl", "FSPCNTLocalLight.glsl")) {
      ReportError(localLightShader->ReportErrors());
      return 0;
   }
   GLSLGraphicsShader* lightingShader = new GLSLGraphicsShader(new TextFileReader());
   if (!lightingShader->ReadShaderSources(
      "VSPCNTLighting.glsl", "FSPCNTLighting.glsl")) {
      ReportError(lightingShader->ReportErrors());
      return 0;
   }

   graphics->AddShader("Simple3DShader", simple3DShader);
   graphics->AddShader("SimplePCTShader", simplePCTShader);
   graphics->AddShader("AmbientLightShader", ambientLightShader);
   graphics->AddShader("GlobalLightShader", globalLightShader);
   graphics->AddShader("LocalLightShader", localLightShader);
   graphics->AddShader("LightingShader", lightingShader);

   GLSLGraphicsShader* currentShader = ambientLightShader;

   OpenGLTexture* wallTexture = new OpenGLTexture();
   wallTexture->LoadFromFile("brickwall.jpg");
   wallTexture->SetMagFilter(GL_LINEAR);
   wallTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("brickwall", wallTexture);

   OpenGLGraphicsObject* wall = Generate::NormalizedTexturedCuboid(10, 1, 10, { 1.0f, 1.0f, 1.0f, 1.0f }, 5.0f, 5.0f);
   wall->SetTexture(wallTexture);
   graphics->scene->AddObject("wall", wall, currentShader);
   wall->frame.Move({ 0.0f, 5.0f, -5.0f });

   OpenGLTexture* crateTexture = new OpenGLTexture();
   crateTexture->LoadFromFile("crate.jpg");
   graphics->AddTexture("crate", crateTexture);

   OpenGLTexture* metalTexture = new OpenGLTexture();
   metalTexture->LoadFromFile("metal.jpg");
   graphics->AddTexture("metal", metalTexture);

   OpenGLGraphicsObject* crate1 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate1->SetTexture(metalTexture);
   graphics->scene->AddObject("crate1", crate1, currentShader);
   crate1->frame.Move({ -3.0f, 1.0f, 0.0f });

   OpenGLGraphicsObject* crate2 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate2->SetTexture(crateTexture);
   graphics->scene->AddObject("crate2", crate2, currentShader);
   crate2->frame.Move({ 0.0f, 1.0f, 0.0f });

   OpenGLGraphicsObject* crate3 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate3->SetTexture(metalTexture);
   graphics->scene->AddObject("crate3", crate3, currentShader);
   crate3->frame.Move({ 3.0f, 1.0f, 0.0f });

   OpenGLGraphicsObject* crate4 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate4->SetTexture(crateTexture);
   graphics->scene->AddObject("crate4", crate4, currentShader);
   crate4->frame.Move({ 0.0f, 7.0f, -3.0f });

   auto rotateAnimation1 = new RotateAnimation(30);
   graphics->AddAnimation("RotateAnimation1", rotateAnimation1);
   auto rotateAnimation2 = new RotateAnimation(60);
   graphics->AddAnimation("RotateAnimation2", rotateAnimation2);
   auto rotateAnimation3 = new RotateAnimation(90);
   graphics->AddAnimation("RotateAnimation3", rotateAnimation3);
   auto rotateAnimation4 = new RotateAnimation(15);
   graphics->AddAnimation("RotateAnimation4", rotateAnimation4);

   graphics->scene->SetObjectsAnimation("crate1", rotateAnimation1);
   graphics->scene->SetObjectsAnimation("crate2", rotateAnimation2);
   graphics->scene->SetObjectsAnimation("crate3", rotateAnimation3);
   graphics->scene->SetObjectsAnimation("crate4", rotateAnimation4);

   OpenGLTexture* floorTexture = new OpenGLTexture();
   floorTexture->LoadFromFile("marble-stone-floor.jpg");
   floorTexture->SetMagFilter(GL_LINEAR);
   floorTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("marbleFloor", floorTexture);

   OpenGLGraphicsObject* floor = Generate::NormalizedTexturedFlatSurface(50, 50, { 1.0f, 1.0f, 1.0f, 1.0f }, 50.0f, 50.0f);
   floor->SetTexture(floorTexture);
   graphics->scene->AddObject("floor", floor, currentShader);

   OpenGLTexture* skyTexture = new OpenGLTexture();
   skyTexture->LoadFromFile("sky.jpg");
   skyTexture->SetMagFilter(GL_LINEAR);
   skyTexture->SetMinFilter(GL_LINEAR);
   graphics->AddTexture("sky", skyTexture);

   OpenGLGraphicsObject* sky = Generate::TexturedFlatSurface(100, 100, { 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1);
   sky->SetTexture(skyTexture);
   graphics->scene->AddObject("sky", sky, simplePCTShader);
   sky->frame.Move({ 0.0f, 15.0f, 0.0f });
   sky->frame.Rotate(180.0f, wall->frame.GetXAxis());

   OpenGLGraphicsObject* cube = Generate::Cuboid(0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   graphics->scene->AddObject("cube", cube, simple3DShader);
   cube->frame.Move({ 0.0f, 0.5f, 3.5f });
   graphics->scene->localLight.position = { 0.0f, 0.5f, 3.5f };

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