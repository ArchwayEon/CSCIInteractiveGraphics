#include "MyScene.h"
#include "GLSLGraphicsShader.h"
#include "AbstractGraphicsSystem.h"
#include "TextFileReader.h"
#include "OpenGLGraphicsObject.h"
#include "Generate.h"
#include "OpenGLTexture.h"
#include "RotateAnimation.h"

bool MyScene::LoadScene()
{
   if (!LoadShaders()) {
      return false;
   }
   if (!LoadTextures()) {
      return false;
   }
   if (!LoadAnimations()) {
      return false;
   }
   if (!LoadObjects()) {
      return false;
   }
   if (!LoadLights()) {
      return false;
   }
   return true;
}

bool MyScene::LoadShaders()
{
   GLSLGraphicsShader* simple3DShader = new GLSLGraphicsShader(new TextFileReader());
   if (!simple3DShader->ReadShaderSources(
      "Simple3DVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      AddError(simple3DShader->ReportErrors());
      return false;
   }
   GLSLGraphicsShader* simplePCTShader = new GLSLGraphicsShader(new TextFileReader());
   if (!simplePCTShader->ReadShaderSources(
      "VSPositionColorTexture.glsl", "FSPositionColorTexture.glsl")) {
      AddError(simplePCTShader->ReportErrors());
      return false;
   }
   GLSLGraphicsShader* lightingShader = new GLSLGraphicsShader(new TextFileReader());
   if (!lightingShader->ReadShaderSources(
      "VSPCNTLighting.glsl", "FSPCNTLighting.glsl")) {
      AddError(lightingShader->ReportErrors());
      return false;
   }
   _graphics->AddShader("simple3DShader", simple3DShader);
   _graphics->AddShader("simplePCTShader", simplePCTShader);
   _graphics->AddShader("lightingShader", lightingShader);
   return true;
}

bool MyScene::LoadTextures()
{
   OpenGLTexture* floorTexture = new OpenGLTexture();
   floorTexture->LoadFromFile("wood_floor.jpg");
   floorTexture->SetMagFilter(GL_LINEAR);
   floorTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("floorTexture", floorTexture);

   OpenGLTexture* plutoTexture = new OpenGLTexture();
   plutoTexture->LoadFromFile("pluto_texture.jpg");
   plutoTexture->SetMagFilter(GL_LINEAR);
   plutoTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("plutoTexture", plutoTexture);

   OpenGLTexture* metalTexture = new OpenGLTexture();
   metalTexture->LoadFromFile("metal.jpg");
   metalTexture->SetMagFilter(GL_LINEAR);
   metalTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("metalTexture", metalTexture);

   OpenGLTexture* smileyTexture = new OpenGLTexture();
   smileyTexture->LoadFromFile("smiley.jpg");
   smileyTexture->SetMagFilter(GL_LINEAR);
   smileyTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("smileyTexture", smileyTexture);

   return true;
}

bool MyScene::LoadAnimations()
{
   auto rotateAnimation1 = new RotateAnimation(30);
   _graphics->AddAnimation("rotateAnimation1", rotateAnimation1);
   return true;
}

bool MyScene::LoadObjects()
{
   auto lightingShader = _graphics->GetShader("lightingShader");
   OpenGLGraphicsObject* floor =
      Generate::NormalizedTexturedFlatSurface(
         50, 50, 50, 50, { 1.0f, 1.0f, 1.0f, 1.0f }, 
         50.0f, 50.0f);
   floor->SetTexture(_graphics->GetTexture("floorTexture"));
   AddObject("floor", floor, lightingShader);

   OpenGLGraphicsObject* pluto =
      Generate::Sphere(
         2, 18, 18,
         { 1.0f, 1.0f, 1.0f, 1.0f },
         SphereShadingType::Smooth_Shading);
   pluto->SetTexture(_graphics->GetTexture("plutoTexture"));
   AddObject("pluto", pluto, lightingShader);
   pluto->frame.Move({ 0.0f, 4.0f, -5.0f });
   pluto->material.specularIntensity = 0.9f;
   pluto->material.shininess = 256;

   SetObjectsAnimation("pluto", _graphics->GetAnimation("rotateAnimation1"));

   OpenGLGraphicsObject* cylinder =
      Generate::Cylinder(
         2, 2, 18, 18,
         { 1.0f, 1.0f, 1.0f, 1.0f },
         SphereShadingType::Smooth_Shading);
   cylinder->SetTexture(_graphics->GetTexture("smileyTexture"));
   AddObject("cylinder", cylinder, lightingShader);
   cylinder->material.specularIntensity = 0.9f;
   cylinder->material.shininess = 256;

   cylinder->frame.Move({ 0.0f, 6.0f, 0.0f });

   auto simple3DShader = _graphics->GetShader("simple3DShader");
   OpenGLGraphicsObject* axis = Generate::Axis();
   AddObject("axis", axis, simple3DShader);

   OpenGLGraphicsObject* lamp1 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   AddObject("lamp1", lamp1, simple3DShader);
   lamp1->frame.Move({ 10.0f, 0.5f, 13.5f });

   OpenGLGraphicsObject* lamp2 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 0.0f, 1.0f });
   AddObject("lamp2", lamp2, simple3DShader);
   lamp2->frame.Move({ -2.5f, 13.5f, -12.5f });

   OpenGLGraphicsObject* lamp3 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 0.0f, 1.0f, 1.0f });
   AddObject("lamp3", lamp3, simple3DShader);
   lamp3->frame.Move({ 2.5f, 3.5f, 2.5f });

   OpenGLGraphicsObject* lamp4 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 0.0f, 1.0f, 0.0f, 1.0f });
   AddObject("lamp4", lamp4, simple3DShader);
   lamp4->frame.Move({ 0, 10, 0 });

   return true;
}

bool MyScene::LoadLights()
{
   globalLight.intensity = 0.06f;

   auto object = GetGraphicsObject("lamp1");
   auto pos = object->frame.GetPosition();
   localLight[0].position = { pos.x, pos.y, pos.z };
   localLight[0].color = { 1, 1, 1 };
   localLight[0].intensity = 0.1f;

   auto index = AddLight();
   object = GetGraphicsObject("lamp2");
   pos = object->frame.GetPosition();
   localLight[index].position = { pos.x, pos.y, pos.z };
   localLight[index].color = { 1, 1, 0 };
   localLight[index].intensity = 0.8f;

   index = AddLight();
   object = GetGraphicsObject("lamp3");
   pos = object->frame.GetPosition();
   localLight[index].position = { pos.x, pos.y, pos.z };
   localLight[index].color = { 1, 0, 1 };
   localLight[index].intensity = 0.5f;

   index = AddLight();
   object = GetGraphicsObject("lamp4");
   pos = object->frame.GetPosition();
   localLight[index].position = { pos.x, pos.y, pos.z };
   localLight[index].color = { 0, 1, 0 };
   localLight[index].intensity = 0.9f;

   return true;
}
