#include "MyScene.h"
#include "GLSLGraphicsShader.h"
#include "AbstractGraphicsSystem.h"
#include "TextFileReader.h"
#include "OpenGLGraphicsObject.h"
#include "Generate.h"
#include "OpenGLTexture.h"
#include "RotateAnimation.h"
#include "BackForthAnimation.h"
#include <vector>

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

void MyScene::Update(double elapsedSeconds)
{
   BaseGraphicsScene::Update(elapsedSeconds);
   camera->SetupViewingFrustum(5.0f);
   camera->OrientViewingFrustum();
   vector<AbstractGraphicsObject*> collidingObjects;
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      auto object = iterator->second;
      for (auto iter = _objects.begin(); iter != _objects.end(); iter++) {
         auto object2 = iter->second;
         if (object == object2) continue;

         if (object->boundingSphere.OverlapsWith(object2->boundingSphere)) {
            collidingObjects.push_back(object);
            collidingObjects.push_back(object2);
         }
      }
      if (camera->viewingFrustum.HasSphereInside(object->boundingSphere)) {
         object->material.ambientIntensity = 0.5f;
      }
      else {
         object->material.ambientIntensity = 0.05f;
      }
   }

   for (auto i = 0; i < collidingObjects.size(); i++) {
      collidingObjects[i]->material.ambientIntensity = 0.5;
   }
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

   OpenGLTexture* crateTexture = new OpenGLTexture();
   crateTexture->LoadFromFile("crate.jpg");
   crateTexture->SetMagFilter(GL_LINEAR);
   crateTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("crateTexture", crateTexture);

   return true;
}

bool MyScene::LoadAnimations()
{
   auto rotateAnimation1 = new RotateAnimation(30);
   _graphics->AddAnimation("rotateAnimation1", rotateAnimation1);

   auto bf1 = new BackForthAnimation(1, 5);
   _graphics->AddAnimation("bf1", bf1);

   auto bf2 = new BackForthAnimation(3, 10);
   _graphics->AddAnimation("bf2", bf2);

   auto bf3 = new BackForthAnimation(5, 20);
   _graphics->AddAnimation("bf3", bf3);

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
   pluto->frame.Move({ 0.0f, 8.0f, -5.0f });
   pluto->material.specularIntensity = 0.9f;
   pluto->material.shininess = 256;
   pluto->boundingSphere.radius = 2.0f;

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
   cylinder->frame.Rotate(180.0f, cylinder->frame.GetYAxis());
   SetObjectsAnimation("cylinder", _graphics->GetAnimation("bf3"));


   OpenGLGraphicsObject* crate1 =
      Generate::Cuboid( "NormalizedTextured", 2, 2, 2, { 1.0f, 0.0f, 1.0f, 1.0f });
   crate1->SetTexture(_graphics->GetTexture("crateTexture"));
   AddObject("crate1", crate1, lightingShader);
   crate1->frame.Move({ -4.0f, 2.0f, -4.0f });
   crate1->material.ambientIntensity = 0.05f;

   SetObjectsAnimation("crate1", _graphics->GetAnimation("bf1"));

   OpenGLGraphicsObject* crate2 =
      Generate::Cuboid("NormalizedTextured", 2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate2->SetTexture(_graphics->GetTexture("crateTexture"));
   AddObject("crate2", crate2, lightingShader);
   crate2->frame.Move({ -4.0f, 2.0f, 4.0f });
   crate2->frame.Rotate(180.0f, crate2->frame.GetYAxis());
   crate2->material.ambientIntensity = 0.05f;

   SetObjectsAnimation("crate2", _graphics->GetAnimation("bf2"));

   OpenGLGraphicsObject* crate3 =
      Generate::Cuboid("NormalizedTextured", 2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate3->SetTexture(_graphics->GetTexture("crateTexture"));
   AddObject("crate3", crate3, lightingShader);
   crate3->frame.Move({ 4.0f, 2.0f, 4.0f });
   crate3->material.ambientIntensity = 0.05f;

   OpenGLGraphicsObject* crate4 =
      Generate::Cuboid("NormalizedTextured", 2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate4->SetTexture(_graphics->GetTexture("crateTexture"));
   AddObject("crate4", crate4, lightingShader);
   crate4->frame.Move({ 4.0f, 2.0f, -4.0f });
   crate4->material.ambientIntensity = 0.05f;

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
