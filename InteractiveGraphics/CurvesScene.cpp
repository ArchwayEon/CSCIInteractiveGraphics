#include "CurvesScene.h"
#include "GLSLGraphicsShader.h"
#include "AbstractGraphicsSystem.h"
#include "TextFileReader.h"
#include "OpenGLGraphicsObject.h"
#include "Generate.h"
#include "OpenGLTexture.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

bool CurvesScene::LoadScene()
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

bool CurvesScene::LoadShaders()
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

bool CurvesScene::LoadTextures()
{
   OpenGLTexture* floorTexture = new OpenGLTexture();
   floorTexture->LoadFromFile("wood_floor.jpg");
   floorTexture->SetMagFilter(GL_LINEAR_MIPMAP_LINEAR);
   floorTexture->SetMinFilter(GL_LINEAR_MIPMAP_LINEAR);
   _graphics->AddTexture("floorTexture", floorTexture);

   OpenGLTexture* grassTexture = new OpenGLTexture();
   grassTexture->LoadFromFile("grass.jpg");
   grassTexture->SetMagFilter(GL_LINEAR_MIPMAP_LINEAR);
   grassTexture->SetMinFilter(GL_LINEAR_MIPMAP_LINEAR);
   _graphics->AddTexture("grassTexture", grassTexture);
   return true;
}

bool CurvesScene::LoadAnimations()
{
   return true;
}

bool CurvesScene::LoadObjects()
{
   auto lightingShader = _graphics->GetShader("lightingShader");
   //OpenGLGraphicsObject* floor =
   //   Generate::NormalizedTexturedFlatSurface(
   //      50, 50, 50, 50, { 1.0f, 1.0f, 1.0f, 1.0f },
   //      50.0f, 50.0f);
   //floor->SetTexture(_graphics->GetTexture("floorTexture"));
   //AddObject("floor", floor, lightingShader);

   auto simple3DShader = _graphics->GetShader("simple3DShader");
   OpenGLGraphicsObject* axis = Generate::Axis();
   AddObject("axis", axis, simple3DShader);

   //OpenGLGraphicsObject* circle = Generate::Circle(3, { 1, 0, 0, 1 });
   //circle->frame.Move({ 0, 3, -20 });
   //AddObject("circle", circle, simple3DShader);

   //OpenGLGraphicsObject* spirograph = 
   //   Generate::Spirograph(4, 0.955f, 0.55f, { 1, 0, 1, 1 }, 20);
   //spirograph->frame.Move({ 0, 4, -10 });
   //AddObject("spirograph", spirograph, simple3DShader);

   //glm::vec3 points[3];
   //glm::vec3 points[4];
   //points[0] = { -2, 0, 0 };
   //points[1] = { 0, 5, 0 };
   //points[2] = { 2, -5, 0 };
   //points[3] = { 2, 0, 0 };
   //OpenGLGraphicsObject* qbezier =
   //   Generate::QuadraticBezier(points, { 0, 1, 0, 1 });
   //qbezier->frame.Move({ 0, 0, 0 });
   //AddObject("qbezier", qbezier, simple3DShader);
   //OpenGLGraphicsObject* cbezier =
   //   Generate::CubicBezier(points, { 0, 1, 0, 1 }, 20);
   //cbezier->frame.Move({ 0, 0, 0 });
   //AddObject("cbezier", cbezier, simple3DShader);
   //OpenGLGraphicsObject* qbezier =
   //Generate::QuadraticBezierM(points, { 0, 1, 0, 1 });
   //qbezier->frame.Move({ 0, 0, 0 });
   //AddObject("qbezier", qbezier, simple3DShader);
   //OpenGLGraphicsObject* cbezier =
   //   Generate::CubicBezierM(points, { 0, 1, 0, 1 }, 20);
   //cbezier->frame.Move({ 0, 0, 0 });
   //AddObject("cbezier", cbezier, simple3DShader);

   //OpenGLGraphicsObject* p0 = Generate::Cuboid(
   //   0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   //AddObject("p0", p0, simple3DShader);
   //p0->frame.Move(points[0]);

   //OpenGLGraphicsObject* p1 = Generate::Cuboid(
   //   0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   //AddObject("p1", p1, simple3DShader);
   //p1->frame.Move(points[1]);

   //OpenGLGraphicsObject* p2 = Generate::Cuboid(
   //   0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   //AddObject("p2", p2, simple3DShader);
   //p2->frame.Move(points[2]);

   //OpenGLGraphicsObject* p3 = Generate::Cuboid(
   //   0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   //AddObject("p3", p3, simple3DShader);
   //p3->frame.Move(points[3]);

   srand((unsigned int)time(nullptr)); // Initialize the randon seed
   glm::vec3 spoints[4][4];
   spoints[0][0] = { -10,  1, -10 };
   spoints[1][0] = { -10,  3, -3.33 };
   spoints[2][0] = { -10, -3,  3.34 };
   spoints[3][0] = { -10,  2,  10 };

   spoints[0][1] = { -3.33,  0, -10 };
   spoints[1][1] = { -3.33,  3, -3.33 };
   spoints[2][1] = { -3.33, -3,  3.34 };
   spoints[3][1] = { -3.33,  -3, 10 };

   spoints[0][2] = { 3.34,  2, -10 };
   spoints[1][2] = { 3.34,  3, -3.33 };
   spoints[2][2] = { 3.34, -3,  3.34 };
   spoints[3][2] = { 3.34,  1,  10 };

   spoints[0][3] = { 10,  -2, -10 };
   spoints[1][3] = { 10,  3,  -3.33 };
   spoints[2][3] = { 10, -3,   3.34 };
   spoints[3][3] = { 10,  -2,  10 };
   srand((unsigned int)time(nullptr)); // Initialize the randon seed
   for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
         spoints[row][col].y = (float)((rand() % 9) - 4);
      }
   }
   //OpenGLGraphicsObject* bezierSurface =
   //   Generate::CubicBezierPatch(spoints, { 0, 1, 0, 1 }, 10);
   OpenGLGraphicsObject* bezierSurface =
      Generate::TexturedBezierPatch(spoints, { 1, 1, 1, 1 }, 10, 10, 10);
   bezierSurface->SetTexture(_graphics->GetTexture("grassTexture"));
   AddObject("bezierSurface", bezierSurface, lightingShader);

   OpenGLGraphicsObject* lamp1 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
   AddObject("lamp1", lamp1, simple3DShader);
   lamp1->frame.Move({ 0.0f, 2.0f, 0.0f });

   OpenGLGraphicsObject* lamp2 = Generate::Cuboid(
      0.1f, 0.1f, 0.1f, { 0.0f, 1.0f, 0.0f, 1.0f });
   AddObject("lamp2", lamp2, simple3DShader);
   lamp2->frame.Move({ -5.0f, 3.0f, -5.0f });

   OpenGLGraphicsObject* cp;
   for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
         cp = Generate::Cuboid(
            0.1f, 0.1f, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f });
         AddObject("cp" + std::to_string(row) + std::to_string(col), cp, simple3DShader);
         cp->frame.Move(spoints[row][col]);
      }
   }

   return true;
}

bool CurvesScene::LoadLights()
{
   globalLight.intensity = 0.3f;

   auto object = GetGraphicsObject("lamp1");
   auto pos = object->frame.GetPosition();
   localLight[0].position = { pos.x, pos.y, pos.z };
   localLight[0].color = { 1, 1, 1 };
   localLight[0].intensity = 0.3f;

   auto index = AddLight();
   object = GetGraphicsObject("lamp2");
   pos = object->frame.GetPosition();
   localLight[index].position = { pos.x, pos.y, pos.z };
   localLight[index].color = { 0, 1, 0 };
   localLight[index].intensity = 0.8f;

   return true;
}
