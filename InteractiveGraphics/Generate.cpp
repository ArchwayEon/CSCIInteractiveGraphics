#include "Generate.h"

OpenGLGraphicsObject* Generate::FlatSurface(float width, float depth, RGBA color)
{
   auto flatSurface = new OpenGLGraphicsObject();
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   Vertex V1 = { -halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
   Vertex V2 = { -halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
   Vertex V3 = {  halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
   Vertex V4 = {  halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
   flatSurface->AddVertex(V1);
   flatSurface->AddVertex(V2);
   flatSurface->AddVertex(V3);
   flatSurface->AddVertex(V1);
   flatSurface->AddVertex(V3);
   flatSurface->AddVertex(V4);
   return flatSurface;
}

OpenGLGraphicsObject* Generate::Cuboid(float width, float depth, float height, RGBA color)
{
   auto cuboid = new OpenGLGraphicsObject();
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float halfHeight = height / 2;
   Vertex V1 = { -halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue };
   Vertex V2 = { -halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue };
   Vertex V3 = {  halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue };
   Vertex V4 = {  halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue };

   Vertex V5 = {  halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue };
   Vertex V6 = {  halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue };
   Vertex V7 = { -halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue };
   Vertex V8 = { -halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue };
   // Face 1
   cuboid->AddVertex(V1);
   cuboid->AddVertex(V2);
   cuboid->AddVertex(V3);
   cuboid->AddVertex(V1);
   cuboid->AddVertex(V3);
   cuboid->AddVertex(V4);
   // Face 2
   cuboid->AddVertex(V4);
   cuboid->AddVertex(V3);
   cuboid->AddVertex(V6);
   cuboid->AddVertex(V4);
   cuboid->AddVertex(V6);
   cuboid->AddVertex(V5);
   // Face 3
   cuboid->AddVertex(V5);
   cuboid->AddVertex(V6);
   cuboid->AddVertex(V7);
   cuboid->AddVertex(V5);
   cuboid->AddVertex(V7);
   cuboid->AddVertex(V8);
   // Face 4
   cuboid->AddVertex(V8);
   cuboid->AddVertex(V7);
   cuboid->AddVertex(V2);
   cuboid->AddVertex(V8);
   cuboid->AddVertex(V2);
   cuboid->AddVertex(V1);
   // Face 5
   cuboid->AddVertex(V6);
   cuboid->AddVertex(V3);
   cuboid->AddVertex(V2);
   cuboid->AddVertex(V6);
   cuboid->AddVertex(V2);
   cuboid->AddVertex(V7);
   // Face 6
   cuboid->AddVertex(V8);
   cuboid->AddVertex(V1);
   cuboid->AddVertex(V4);
   cuboid->AddVertex(V8);
   cuboid->AddVertex(V4);
   cuboid->AddVertex(V5);
   return cuboid;
}
