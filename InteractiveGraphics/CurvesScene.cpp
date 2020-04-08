#include "CurvesScene.h"
#include "GLSLGraphicsShader.h"
#include "AbstractGraphicsSystem.h"
#include "TextFileReader.h"
#include "OpenGLGraphicsObject.h"
#include "Generate.h"
#include "OpenGLTexture.h"

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
   floorTexture->SetMagFilter(GL_LINEAR);
   floorTexture->SetMinFilter(GL_LINEAR);
   _graphics->AddTexture("floorTexture", floorTexture);
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

   glm::vec3 spoints[4][4];
   spoints[0][0] = { -4,  1, -4 };
   spoints[1][0] = { -4,  3, -2 };
   spoints[2][0] = { -4, -3,  2 };
   spoints[3][0] = { -4,  2,  4 };

   spoints[0][1] = { -2,  0, -4 };
   spoints[1][1] = { -2,  3, -2 };
   spoints[2][1] = { -2, -3,  2 };
   spoints[3][1] = { -2,  -3, 4 };

   spoints[0][2] = { 2,  2, -4 };
   spoints[1][2] = { 2,  3, -2 };
   spoints[2][2] = { 2, -3,  2 };
   spoints[3][2] = { 2,  1,  4 };

   spoints[0][3] = { 4,  -2, -4 };
   spoints[1][3] = { 4,  3,  -2 };
   spoints[2][3] = { 4, -3,   2 };
   spoints[3][3] = { 4,  -2,  4 };
   OpenGLGraphicsObject* bezierSurface =
      Generate::CubicBezierPatch(spoints, { 0, 1, 0, 1 }, 20);
   AddObject("bezierSurface", bezierSurface, simple3DShader);

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
   globalLight.intensity = 0.1f;
   return true;
}
