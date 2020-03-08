#include "Generate.h"
#include "OpenGLVertexPCStrategy.h"
#include "OpenGLIndexedVertexPCStrategy.h"
#include "OpenGLVertexPCTStrategy.h"

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

OpenGLGraphicsObject* Generate::TexturedFlatSurface(float width, float depth, RGBA color)
{
   auto flatSurface = new OpenGLGraphicsObject();
   flatSurface->vertexStrategy = new OpenGLVertexPCTStrategy();
   auto vertexStrategy = (OpenGLVertexPCTStrategy*)flatSurface->vertexStrategy;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   VertexPCT V1 = { 
      -halfWidth, 0.0f, -halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      0.0f, 1.0f
   };
   VertexPCT V2 = { 
      -halfWidth, 0.0f,  halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      0.0f, 0.0f
   };
   VertexPCT V3 = { 
      halfWidth, 0.0f,  halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      1.0f, 0.0f
   };
   VertexPCT V4 = { 
      halfWidth, 0.0f, -halfDepth, 
      color.red, color.green, color.blue, color.alpha,
      1.0f, 1.0f
   };
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V2);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V1);
   vertexStrategy->AddVertex(V3);
   vertexStrategy->AddVertex(V4);
   return flatSurface;
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
