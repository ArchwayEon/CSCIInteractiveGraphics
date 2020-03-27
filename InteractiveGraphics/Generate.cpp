#include "Generate.h"
#include "OpenGLVertexPCStrategy.h"
#include "OpenGLIndexedVertexPCStrategy.h"
#include "OpenGLVertexPCTStrategy.h"
#include "OpenGLVertexPCNTStrategy.h"

OpenGLGraphicsObject* Generate::FlatSurface(string type, float width, float depth, RGBA color, float maxS, float maxT)
{
   if (type == "Plain") return Generate::FlatSurface(width, depth, color);
   if (type == "Textured") return Generate::TexturedFlatSurface(width, depth, color, maxS, maxT);
   if (type == "NormalizedTextured") return Generate::NormalizedTexturedFlatSurface(
      width, depth, color, maxS, maxT);
   return nullptr;
}

OpenGLGraphicsObject* Generate::FlatSurface(float width, float depth, RGBA color)
{
   auto flatSurface = new OpenGLGraphicsObject();
   flatSurface->vertexStrategy = new OpenGLVertexPCStrategy();
   auto vertexStrategy = (OpenGLVertexPCStrategy*)flatSurface->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   VertexPC V1 = { -halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
   VertexPC V2 = { -halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
   VertexPC V3 = {  halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
   VertexPC V4 = {  halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   return flatSurface;
}

OpenGLGraphicsObject* Generate::TexturedFlatSurface(float width, float depth, RGBA color, float maxS, float maxT)
{
   auto flatSurface = new OpenGLGraphicsObject();
   flatSurface->vertexStrategy = new OpenGLVertexPCTStrategy();
   auto vertexStrategy = (OpenGLVertexPCTStrategy*)flatSurface->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   VertexPCT V1 = { 
      -halfWidth, 0.0f, -halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      0.0f, maxT
   };
   VertexPCT V2 = { 
      -halfWidth, 0.0f,  halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      0.0f, 0.0f
   };
   VertexPCT V3 = { 
      halfWidth, 0.0f,  halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      maxS, 0.0f
   };
   VertexPCT V4 = { 
      halfWidth, 0.0f, -halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      maxS, maxT
   };
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   return flatSurface;
}

OpenGLGraphicsObject* Generate::NormalizedTexturedFlatSurface(float width, float depth, RGBA color, float maxS, float maxT)
{
   auto flatSurface = new OpenGLGraphicsObject();
   flatSurface->vertexStrategy = new OpenGLVertexPCNTStrategy();
   auto vertexStrategy = (OpenGLVertexPCNTStrategy*)flatSurface->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   VertexPCNT V1 = {
      -halfWidth, 0.0f, -halfDepth,
      color.red, color.green, color.blue, color.alpha,
      0.0f, 1.0f, 0.0f, 
      0.0f, maxT
   };
   VertexPCNT V2 = {
      -halfWidth, 0.0f,  halfDepth,
      color.red, color.green, color.blue, color.alpha,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f
   };
   VertexPCNT V3 = {
      halfWidth, 0.0f,  halfDepth,
      color.red, color.green, color.blue, color.alpha,
      0.0f, 1.0f, 0.0f,
      maxS, 0.0f
   };
   VertexPCNT V4 = {
      halfWidth, 0.0f, -halfDepth,
      color.red, color.green, color.blue, color.alpha,
      0.0f, 1.0f, 0.0f,
      maxS, maxT
   };
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   return flatSurface;
}

OpenGLGraphicsObject* Generate::Cuboid(string type, float width, float depth, float height, RGBA color, float maxS, float maxT)
{
   if (type == "Plain") return Generate::Cuboid(width, depth, height, color);
   if (type == "Textured") return Generate::TexturedCuboid(width, depth, height, color, maxS, maxT);
   if (type == "NormalizedTextured") 
      return Generate::NormalizedTexturedCuboid(width, depth, height, color, maxS, maxT);
   return nullptr;
}

OpenGLGraphicsObject* Generate::Cuboid(float width, float depth, float height, RGBA color)
{
   auto cuboid = new OpenGLGraphicsObject();
   cuboid->vertexStrategy = new OpenGLVertexPCStrategy();
   auto vertexStrategy = (OpenGLVertexPCStrategy*)cuboid->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float halfHeight = height / 2;
   VertexPC V1 = { -halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue };
   VertexPC V2 = { -halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue };
   VertexPC V3 = {  halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue };
   VertexPC V4 = {  halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue };

   VertexPC V5 = {  halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue };
   VertexPC V6 = {  halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue };
   VertexPC V7 = { -halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue };
   VertexPC V8 = { -halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue };
   // Face 1
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   // Face 2
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V5);
   // Face 3
   vertexStrategy->AddVertex(V5);
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V7);
   vertexStrategy->AddVertex(V5);
   vertexStrategy->AddVertex(V7);
   vertexStrategy->AddVertex(V8);
   // Face 4
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V7);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V1);
   // Face 5
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V7);
   // Face 6
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V5);
   return cuboid;
}

OpenGLGraphicsObject* Generate::Axis(float xLength, float yLength, float zLength)
{
   auto axis = new OpenGLGraphicsObject();
   axis->SetPrimitiveType(GL_LINES);
   axis->vertexStrategy = new OpenGLVertexPCStrategy();
   auto vertexStrategy = (OpenGLVertexPCStrategy*)axis->vertexStrategy;
   VertexPC V1 = { 0, 0, 0, 1, 0, 0 };
   VertexPC V2 = { xLength, 0, 0, 1, 0, 0 };
   VertexPC V3 = { 0, 0, 0, 0, 1, 0 };
   VertexPC V4 = { 0, yLength, 0, 0, 1, 0 };
   VertexPC V5 = { 0, 0, 0, 0, 0, 1 };
   VertexPC V6 = { 0, 0, zLength, 0, 0, 1 };
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V5);
   vertexStrategy->AddVertex(V6);
   return axis;
}

OpenGLIndexedGraphicsObject* Generate::IndexedFlatSurface(float width, float depth, RGBA color)
{
   auto flatSurface = new OpenGLIndexedGraphicsObject();
   flatSurface->vertexStrategy = new OpenGLIndexedVertexPCStrategy();
   auto vertexStrategy = (OpenGLIndexedVertexPCStrategy*)flatSurface->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   VertexPC V1 = { -halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
   VertexPC V2 = { -halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
   VertexPC V3 = { halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
   VertexPC V4 = { halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddIndex(0);
   vertexStrategy->AddIndex(1);
   vertexStrategy->AddIndex(2);
   vertexStrategy->AddIndex(0);
   vertexStrategy->AddIndex(2);
   vertexStrategy->AddIndex(3);
   return flatSurface;
}

OpenGLGraphicsObject* Generate::TexturedCuboid(float width, float depth, float height, RGBA color, float maxS, float maxT)
{
   auto cuboid = new OpenGLGraphicsObject();
   cuboid->vertexStrategy = new OpenGLVertexPCTStrategy();
   auto vertexStrategy = (OpenGLVertexPCTStrategy*)cuboid->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float halfHeight = height / 2;
   VertexPCT V1 = { -halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCT V2 = { -halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCT V3 = { halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCT V4 = { halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };

   VertexPCT V5 = { halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCT V6 = { halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCT V7 = { -halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCT V8 = { -halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   // Face 1
   V1.tex = { 0, maxT };
   vertexStrategy->AddVertex(V1);
   V2.tex = { 0, 0 };
   vertexStrategy->AddVertex(V2);
   V3.tex = { maxS, 0 };
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   V4.tex = { maxS, maxT };
   vertexStrategy->AddVertex(V4);
   // Face 2
   V4.tex = { 0, maxT };
   vertexStrategy->AddVertex(V4);
   V3.tex = { 0, 0 };
   vertexStrategy->AddVertex(V3);
   V6.tex = { maxS, 0 };
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V6);
   V5.tex = { maxS, maxT };
   vertexStrategy->AddVertex(V5);
   // Face 3
   V5.tex = { 0, maxT };
   vertexStrategy->AddVertex(V5);
   V6.tex = { 0, 0 };
   vertexStrategy->AddVertex(V6);
   V7.tex = { maxS, 0 };
   vertexStrategy->AddVertex(V7);
   vertexStrategy->AddVertex(V5);
   vertexStrategy->AddVertex(V7);
   V8.tex = { maxS, maxT };
   vertexStrategy->AddVertex(V8);
   // Face 4
   V8.tex = { 0, maxT };
   vertexStrategy->AddVertex(V8);
   V7.tex = { 0, 0 };
   vertexStrategy->AddVertex(V7);
   V2.tex = { maxS, 0 };
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V2);
   V1.tex = { maxS, maxT };
   vertexStrategy->AddVertex(V1);
   // Face 5
   V6.tex = { 0, maxT };
   vertexStrategy->AddVertex(V6);
   V3.tex = { 0, 0 };
   vertexStrategy->AddVertex(V3);
   V2.tex = { maxS, 0 };
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V2);
   V7.tex = { maxS, 1 };
   vertexStrategy->AddVertex(V7);
   // Face 6
   V8.tex = { 0, maxT };
   vertexStrategy->AddVertex(V8);
   V1.tex = { 0, 0 };
   vertexStrategy->AddVertex(V1);
   V4.tex = { maxS, 0 };
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V4);
   V5.tex = { maxS, maxT };
   vertexStrategy->AddVertex(V5);
   return cuboid;
}

OpenGLGraphicsObject* Generate::NormalizedTexturedCuboid(float width, float depth, float height, RGBA color, float maxS, float maxT)
{
   auto cuboid = new OpenGLGraphicsObject();
   cuboid->vertexStrategy = new OpenGLVertexPCNTStrategy();
   auto vertexStrategy = (OpenGLVertexPCNTStrategy*)cuboid->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float halfHeight = height / 2;
   VertexPCNT V1 = { -halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCNT V2 = { -halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCNT V3 = { halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCNT V4 = { halfWidth,  halfHeight, halfDepth, color.red, color.green, color.blue, color.alpha };

   VertexPCNT V5 = { halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCNT V6 = { halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCNT V7 = { -halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   VertexPCNT V8 = { -halfWidth,  halfHeight, -halfDepth, color.red, color.green, color.blue, color.alpha };
   // Face 1
   V1.tex = { 0, maxT };
   V1.normal = { 0, 0, 1 };
   vertexStrategy->AddVertex(V1);
   V2.tex = { 0, 0 };
   V2.normal = { 0, 0, 1 };
   vertexStrategy->AddVertex(V2);
   V3.tex = { maxS, 0 };
   V3.normal = { 0, 0, 1 };
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   V4.tex = { maxS, maxT };
   V4.normal = { 0, 0, 1 };
   vertexStrategy->AddVertex(V4);
   // Face 2
   V4.tex = { 0, maxT };
   V4.normal = { 1, 0, 0 };
   vertexStrategy->AddVertex(V4);
   V3.tex = { 0, 0 };
   V3.normal = { 1, 0, 0 };
   vertexStrategy->AddVertex(V3);
   V6.tex = { maxS, 0 };
   V6.normal = { 1, 0, 0 };
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V6);
   V5.tex = { maxS, maxT };
   V5.normal = { 1, 0, 0 };
   vertexStrategy->AddVertex(V5);
   // Face 3
   V5.tex = { 0, maxT };
   V5.normal = { 0, 0, -1 };
   vertexStrategy->AddVertex(V5);
   V6.tex = { 0, 0 };
   V6.normal = { 0, 0, -1 };
   vertexStrategy->AddVertex(V6);
   V7.tex = { maxS, 0 };
   V7.normal = { 0, 0, -1 };
   vertexStrategy->AddVertex(V7);
   vertexStrategy->AddVertex(V5);
   vertexStrategy->AddVertex(V7);
   V8.tex = { maxS, maxT };
   V8.normal = { 0, 0, -1 };
   vertexStrategy->AddVertex(V8);
   // Face 4
   V8.tex = { 0, maxT };
   V8.normal = { -1, 0, 0 };
   vertexStrategy->AddVertex(V8);
   V7.tex = { 0, 0 };
   V7.normal = { -1, 0, 0 };
   vertexStrategy->AddVertex(V7);
   V2.tex = { maxS, 0 };
   V2.normal = { -1, 0, 0 };
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V2);
   V1.tex = { maxS, maxT };
   V1.normal = { -1, 0, 0 };
   vertexStrategy->AddVertex(V1);
   // Face 5
   V6.tex = { 0, maxT };
   V6.normal = { 0, -1, 0 };
   vertexStrategy->AddVertex(V6);
   V3.tex = { 0, 0 };
   V3.normal = { 0, -1, 0 };
   vertexStrategy->AddVertex(V3);
   V2.tex = { maxS, 0 };
   V2.normal = { 0, -1, 0 };
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V6);
   vertexStrategy->AddVertex(V2);
   V7.tex = { maxS, maxT };
   V7.normal = { 0, -1, 0 };
   vertexStrategy->AddVertex(V7);
   // Face 6
   V8.tex = { 0, maxT };
   V8.normal = { 0, 1, 0 };
   vertexStrategy->AddVertex(V8);
   V1.tex = { 0, 0 };
   V1.normal = { 0, 1, 0 };
   vertexStrategy->AddVertex(V1);
   V4.tex = { maxS, 0 };
   V4.normal = { 0, 1, 0 };
   vertexStrategy->AddVertex(V4);
   vertexStrategy->AddVertex(V8);
   vertexStrategy->AddVertex(V4);
   V5.tex = { maxS, maxT };
   V5.normal = { 0, 1, 0 };
   vertexStrategy->AddVertex(V5);

   return cuboid;

}
