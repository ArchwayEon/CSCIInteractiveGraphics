#include "DefaultGraphicsScene.h"
#include "AbstractGraphicsSystem.h"
#include "BaseCamera.h"
#include "GLSLGraphicsShader.h"
#include "TextFileReader.h"
#include "OpenGLTexture.h"
#include "RotateAnimation.h"
#include "OpenGLGraphicsObject.h"
#include "Generate.h"

bool DefaultGraphicsScene::LoadScene()
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

bool DefaultGraphicsScene::LoadShaders()
{
   // Load the shaders
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
   GLSLGraphicsShader* ambientLightShader = new GLSLGraphicsShader(new TextFileReader());
   if (!ambientLightShader->ReadShaderSources(
      "VSPositionColorTexture.glsl", "FSPCTAmbientLight.glsl")) {
      AddError(ambientLightShader->ReportErrors());
      return false;
   }
   GLSLGraphicsShader* globalLightShader = new GLSLGraphicsShader(new TextFileReader());
   if (!globalLightShader->ReadShaderSources(
      "VSPCNTLighting.glsl", "FSPCNTLight.glsl")) {
      AddError(globalLightShader->ReportErrors());
      return false;
   }
   GLSLGraphicsShader* localLightShader = new GLSLGraphicsShader(new TextFileReader());
   if (!localLightShader->ReadShaderSources(
      "VSPCNTLighting.glsl", "FSPCNTLocalLight.glsl")) {
      AddError(localLightShader->ReportErrors());
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
   _graphics->AddShader("ambientLightShader", ambientLightShader);
   _graphics->AddShader("globalLightShader", globalLightShader);
   _graphics->AddShader("localLightShader", localLightShader);
   _graphics->AddShader("lightingShader", lightingShader);
   return true;
}

bool DefaultGraphicsScene::LoadTextures()
{
   OpenGLTexture* wallTexture = new OpenGLTexture();
   wallTexture->LoadFromFile("brickwall.jpg");
   wallTexture->SetMagFilter(GL_LINEAR);
   wallTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("wallTexture", wallTexture);

   OpenGLTexture* floorTexture = new OpenGLTexture();
   floorTexture->LoadFromFile("marble-stone-floor.jpg");
   floorTexture->SetMagFilter(GL_LINEAR);
   floorTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("floorTexture", floorTexture);

   OpenGLTexture* skyTexture = new OpenGLTexture();
   skyTexture->LoadFromFile("sky.jpg");
   skyTexture->SetMagFilter(GL_LINEAR);
   skyTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("skyTexture", skyTexture);

   OpenGLTexture* crateTexture = new OpenGLTexture();
   crateTexture->LoadFromFile("crate.jpg");
   _graphics->AddTexture("crateTexture", crateTexture);

   OpenGLTexture* metalTexture = new OpenGLTexture();
   metalTexture->LoadFromFile("metal.jpg");
   _graphics->AddTexture("metalTexture", metalTexture);

   OpenGLTexture* smileyTexture = new OpenGLTexture();
   smileyTexture->LoadFromFile("smiley.jpg");
   smileyTexture->SetMagFilter(GL_LINEAR);
   smileyTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("smileyTexture", smileyTexture);

   OpenGLTexture* worldTexture = new OpenGLTexture();
   worldTexture->LoadFromFile("world.jpg");
   worldTexture->SetMagFilter(GL_LINEAR);
   worldTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("worldTexture", worldTexture);
   return true;
}

bool DefaultGraphicsScene::LoadAnimations()
{
   auto rotateAnimation1 = new RotateAnimation(30);
   _graphics->AddAnimation("rotateAnimation1", rotateAnimation1);
   auto rotateAnimation2 = new RotateAnimation(60);
   _graphics->AddAnimation("rotateAnimation2", rotateAnimation2);
   auto rotateAnimation3 = new RotateAnimation(90);
   _graphics->AddAnimation("rotateAnimation3", rotateAnimation3);
   auto rotateAnimation4 = new RotateAnimation(15);
   _graphics->AddAnimation("rotateAnimation4", rotateAnimation4);
   auto rotateAnimation5 = new RotateAnimation(31);
   _graphics->AddAnimation("rotateAnimation5", rotateAnimation5);
   auto rotateAnimation6 = new RotateAnimation(65);
   _graphics->AddAnimation("rotateAnimation6", rotateAnimation6);
   auto rotateAnimation7 = new RotateAnimation(65);
   _graphics->AddAnimation("rotateAnimation7", rotateAnimation7);
   return true;
}

bool DefaultGraphicsScene::LoadObjects()
{
   OpenGLGraphicsObject* wall =
      Generate::NormalizedTexturedMeshedCuboid(
         10, 1, 10,
         { 1.0f, 1.0f, 1.0f, 1.0f },
         5, 1, 5,
         5, 5
         );
   auto lightingShader = _graphics->GetShader("lightingShader");

   wall->SetTexture(_graphics->GetTexture("wallTexture"));
   AddObject("wall", wall, lightingShader);
   wall->frame.Move({ 0.0f, 5.0f, -5.0f });

   OpenGLGraphicsObject* crate1 = 
      Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate1->SetTexture(_graphics->GetTexture("metalTexture"));
   AddObject("crate1", crate1, lightingShader);
   crate1->frame.Move({ -3.0f, 1.0f, 0.0f });
   crate1->material.shininess = 512;

   OpenGLGraphicsObject* crate2 = 
      Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate2->SetTexture(_graphics->GetTexture("crateTexture"));
   AddObject("crate2", crate2, lightingShader);
   crate2->frame.Move({ 0.0f, 1.0f, -2.0f });

   OpenGLGraphicsObject* crate3 = 
      Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate3->SetTexture(_graphics->GetTexture("metalTexture"));
   AddObject("crate3", crate3, lightingShader);
   crate3->frame.Move({ 3.0f, 1.0f, 0.0f });
   crate3->material.shininess = 512;

   OpenGLGraphicsObject* crate4 = Generate::NormalizedTexturedCuboid(2, 2, 2, { 1.0f, 1.0f, 1.0f, 1.0f });
   crate4->SetTexture(_graphics->GetTexture("crateTexture"));
   AddObject("crate4", crate4, lightingShader);
   crate4->frame.Move({ 0.0f, 7.0f, -3.0f });

   OpenGLGraphicsObject* crate5 =
      Generate::NormalizedTexturedMeshedCuboid(
         2, 0.5f, 2,
         { 1.0f, 1.0f, 1.0f, 1.0f },
         12, 1, 12,
         3, 5
         );
   crate5->SetTexture(_graphics->GetTexture("smileyTexture"));
   AddObject("crate5", crate5, lightingShader);
   crate5->frame.Move({ 0.0f, 4.0f, 2.0f });
   crate5->material.shininess = 256;

   OpenGLGraphicsObject* world =
      Generate::Sphere(
         1, 18, 18,
         { 1.0f, 1.0f, 1.0f, 1.0f },
         SphereShadingType::Smooth_Shading);
   world->SetTexture(_graphics->GetTexture("worldTexture"));
   AddObject("world", world, lightingShader);
   world->frame.Move({ -4.0f, 4.0f, 2.0f });
   world->material.specularIntensity = 0.9f;
   world->material.shininess = 256;

   OpenGLGraphicsObject* world2 =
      Generate::Sphere(
         1, 18, 18,
         { 1.0f, 1.0f, 1.0f, 1.0f },
         SphereShadingType::Flat_Shading);
   world2->SetTexture(_graphics->GetTexture("worldTexture"));
   AddObject("world2", world2, lightingShader);
   world2->frame.Move({ 4.0f, 4.0f, 2.0f });
   world2->material.specularIntensity = 0.9f;
   world2->material.shininess = 256;

   SetObjectsAnimation("crate1", _graphics->GetAnimation("rotateAnimation1"));
   SetObjectsAnimation("crate2", _graphics->GetAnimation("rotateAnimation2"));
   SetObjectsAnimation("crate3", _graphics->GetAnimation("rotateAnimation3"));
   SetObjectsAnimation("crate4", _graphics->GetAnimation("rotateAnimation4"));
   SetObjectsAnimation("crate5", _graphics->GetAnimation("rotateAnimation5"));
   SetObjectsAnimation("world", _graphics->GetAnimation("rotateAnimation6"));
   SetObjectsAnimation("world2", _graphics->GetAnimation("rotateAnimation7"));

   OpenGLGraphicsObject* floor =
      Generate::NormalizedTexturedFlatSurface(
         50, 50, 50, 50, { 1.0f, 1.0f, 1.0f, 1.0f }, 100.0f, 100.0f);
   floor->SetTexture(_graphics->GetTexture("floorTexture"));
   AddObject("floor", floor, lightingShader);

   auto simplePCTShader = _graphics->GetShader("simplePCTShader");

   OpenGLGraphicsObject* sky = Generate::TexturedFlatSurface(
      100, 100, { 1.0f, 1.0f, 1.0f, 1.0f }, 1, 1);
   sky->SetTexture(_graphics->GetTexture("skyTexture"));
   AddObject("sky", sky, simplePCTShader);
   sky->frame.Move({ 0.0f, 15.0f, 0.0f });
   sky->frame.Rotate(180.0f, wall->frame.GetXAxis());

   auto simple3DShader = _graphics->GetShader("simple3DShader");

   OpenGLGraphicsObject* lamp = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   AddObject("lamp", lamp, simple3DShader);
   lamp->frame.Move({ 0.0f, 0.5f, 3.5f });
   
   OpenGLGraphicsObject* lamp2 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 0.0f, 1.0f });
   AddObject("lamp2", lamp2, simple3DShader);
   lamp2->frame.Move({ -2.5f, 3.5f, 2.5f });
   
   OpenGLGraphicsObject* lamp3 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 0.0f, 1.0f, 1.0f });
   AddObject("lamp3", lamp3, simple3DShader);
   lamp3->frame.Move({ 2.5f, 3.5f, 2.5f });

   OpenGLGraphicsObject* axis = Generate::Axis();
   AddObject("axis", axis, simple3DShader);

   return true;
}

bool DefaultGraphicsScene::LoadLights()
{
   globalLight.intensity = 0.05f;

   auto object = GetGraphicsObject("lamp");
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

   return true;
}
