#include "Generate.h"
#include "OpenGLVertexPCStrategy.h"
#include "OpenGLIndexedVertexPCStrategy.h"
#include "OpenGLVertexPCTStrategy.h"
#include "OpenGLVertexPCNTStrategy.h"
#include "PolygonMesh.h"
#include "GraphicsStructures.h"

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
   auto mesh = (PolygonMesh*)vertexStrategy->GetMesh();
   mesh->AddVertex(V1);
   mesh->AddVertex(V2);
   mesh->AddVertex(V3);
   mesh->AddVertex(V1);
   mesh->AddVertex(V3);
   mesh->AddVertex(V4);
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
   auto mesh = (PolygonMesh*)vertexStrategy->GetMesh();
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
   mesh->AddVertex(V1);
   V2.tex = { 0, 0 };
   V2.normal = { 0, 0, 1 };
   mesh->AddVertex(V2);
   V3.tex = { maxS, 0 };
   V3.normal = { 0, 0, 1 };
   mesh->AddVertex(V3);
   mesh->AddVertex(V1);
   mesh->AddVertex(V3);
   V4.tex = { maxS, maxT };
   V4.normal = { 0, 0, 1 };
   mesh->AddVertex(V4);
   // Face 2
   V4.tex = { 0, maxT };
   V4.normal = { 1, 0, 0 };
   mesh->AddVertex(V4);
   V3.tex = { 0, 0 };
   V3.normal = { 1, 0, 0 };
   mesh->AddVertex(V3);
   V6.tex = { maxS, 0 };
   V6.normal = { 1, 0, 0 };
   mesh->AddVertex(V6);
   mesh->AddVertex(V4);
   mesh->AddVertex(V6);
   V5.tex = { maxS, maxT };
   V5.normal = { 1, 0, 0 };
   mesh->AddVertex(V5);
   // Face 3
   V5.tex = { 0, maxT };
   V5.normal = { 0, 0, -1 };
   mesh->AddVertex(V5);
   V6.tex = { 0, 0 };
   V6.normal = { 0, 0, -1 };
   mesh->AddVertex(V6);
   V7.tex = { maxS, 0 };
   V7.normal = { 0, 0, -1 };
   mesh->AddVertex(V7);
   mesh->AddVertex(V5);
   mesh->AddVertex(V7);
   V8.tex = { maxS, maxT };
   V8.normal = { 0, 0, -1 };
   mesh->AddVertex(V8);
   // Face 4
   V8.tex = { 0, maxT };
   V8.normal = { -1, 0, 0 };
   mesh->AddVertex(V8);
   V7.tex = { 0, 0 };
   V7.normal = { -1, 0, 0 };
   mesh->AddVertex(V7);
   V2.tex = { maxS, 0 };
   V2.normal = { -1, 0, 0 };
   mesh->AddVertex(V2);
   mesh->AddVertex(V8);
   mesh->AddVertex(V2);
   V1.tex = { maxS, maxT };
   V1.normal = { -1, 0, 0 };
   mesh->AddVertex(V1);
   // Face 5
   V6.tex = { 0, maxT };
   V6.normal = { 0, -1, 0 };
   mesh->AddVertex(V6);
   V3.tex = { 0, 0 };
   V3.normal = { 0, -1, 0 };
   mesh->AddVertex(V3);
   V2.tex = { maxS, 0 };
   V2.normal = { 0, -1, 0 };
   mesh->AddVertex(V2);
   mesh->AddVertex(V6);
   mesh->AddVertex(V2);
   V7.tex = { maxS, maxT };
   V7.normal = { 0, -1, 0 };
   mesh->AddVertex(V7);
   // Face 6
   V8.tex = { 0, maxT };
   V8.normal = { 0, 1, 0 };
   mesh->AddVertex(V8);
   V1.tex = { 0, 0 };
   V1.normal = { 0, 1, 0 };
   mesh->AddVertex(V1);
   V4.tex = { maxS, 0 };
   V4.normal = { 0, 1, 0 };
   mesh->AddVertex(V4);
   mesh->AddVertex(V8);
   mesh->AddVertex(V4);
   V5.tex = { maxS, maxT };
   V5.normal = { 0, 1, 0 };
   mesh->AddVertex(V5);

   return cuboid;

}

OpenGLGraphicsObject* Generate::NormalizedTexturedMeshedCuboid(
   float width, float depth, float height, RGBA color, 
   int widthFacetCount, int depthFacetCount, int heightFacetCount, 
   float maxS, float maxT, float maxSdepth)
{
   auto cuboid = new OpenGLGraphicsObject();
   cuboid->vertexStrategy = new OpenGLVertexPCNTStrategy();
   auto vertexStrategy = (OpenGLVertexPCNTStrategy*)cuboid->vertexStrategy;
   auto mesh = (PolygonMesh*)vertexStrategy->GetMesh();
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float halfHeight = height / 2;
   // Front face
   Generate::NormalizedTexturedFlatMesh(mesh, PlaneType::XY, halfDepth,
      width, height, widthFacetCount, heightFacetCount, color, maxS, maxT);
   // Right face
   Generate::NormalizedTexturedFlatMesh(mesh, PlaneType::YZ, halfWidth,
      depth, height, depthFacetCount, heightFacetCount, color, maxSdepth, maxT);
   // Back face
   Generate::NormalizedTexturedFlatMesh(mesh, PlaneType::XY_Flipped, -halfDepth,
      width, height, widthFacetCount, heightFacetCount, color, maxS, maxT);
   // Left face
   Generate::NormalizedTexturedFlatMesh(mesh, PlaneType::YZ_Flipped, -halfWidth,
      depth, height, depthFacetCount, heightFacetCount, color, maxSdepth, maxT);
   // Top face
   Generate::NormalizedTexturedFlatMesh(mesh, PlaneType::XZ, halfHeight,
      width, depth, widthFacetCount, depthFacetCount, color, maxS, maxSdepth);
   // Bottom face
   Generate::NormalizedTexturedFlatMesh(mesh, PlaneType::XZ_Flipped, -halfHeight,
      width, depth, widthFacetCount, depthFacetCount, color, maxS, maxSdepth);
   return cuboid;
}

void Generate::NormalizedTexturedFlatMesh(
   PolygonMesh* meshToFill, PlaneType plane, float offset, 
   float width, float depth, int widthFacetCount, int depthFacetCount, 
   RGBA color, float textureWidthRepeat, float textureDepthRepeat)
{
   VertexPCNT V1, V2, V3, V4;
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float facetWidth = width / widthFacetCount;
   float facetDepth = depth / depthFacetCount;
   float sDelta = textureWidthRepeat / widthFacetCount;
   float tDelta = textureDepthRepeat / depthFacetCount;
   float startS, startT, endS, endT = textureDepthRepeat;
   float x, y = 0, z = -halfDepth;
   startT = endT - tDelta;
   Vector3 normal;
   switch (plane) {
   case PlaneType::XZ:
      normal = { 0, 1, 0 };
      y = offset;
      z = -halfDepth;
      break;
   case PlaneType::XZ_Flipped:
      normal = { 0, -1, 0 };
      y = offset;
      z = -halfDepth;
      break;
   case PlaneType::XY:
      normal = { 0, 0, 1 };
      y = halfDepth;
      z = offset;
      break;
   case PlaneType::XY_Flipped:
      normal = { 0, 0, -1 };
      y = halfDepth;
      z = offset;
      break;
   case PlaneType::YZ:
      normal = { 1, 0, 0 };
      x = offset;
      y = halfDepth;
      break;
   case PlaneType::YZ_Flipped:
      normal = { -1, 0, 0 };
      x = offset;
      y = halfDepth;
      break;
   }
   for (int row = 1; row <= depthFacetCount; ++row) {
      switch (plane) {
      case PlaneType::XZ:
         x = -halfWidth;
         break;
      case PlaneType::XZ_Flipped:
         x = halfWidth;
         break;
      case PlaneType::XY:
         x = -halfWidth;
         break;
      case PlaneType::XY_Flipped:
         x = halfWidth;
         break;
      case PlaneType::YZ:
         z = halfWidth;
         break;
      case PlaneType::YZ_Flipped:
         z = -halfWidth;
         break;
      }
      startS = 0;
      endT = startT + tDelta;
      for (int col = 1; col <= widthFacetCount; ++col) {
         endS = startS + sDelta;
         if (endS > textureWidthRepeat) endS = textureWidthRepeat;
         V1.position = { x, y, z };
         V1.color = color;
         V1.normal = normal;
         V1.tex = { startS, endT };

         switch (plane) {
         case PlaneType::XZ:
            V2.position = { x, y, z + facetDepth };
            break;
         case PlaneType::XZ_Flipped:
            V2.position = { x, y, z + facetDepth };
            break;
         case PlaneType::XY:
         case PlaneType::XY_Flipped:
         case PlaneType::YZ:
         case PlaneType::YZ_Flipped:
            V2.position = { x, y - facetDepth, z };
            break;
         }
         V2.color = color;
         V2.normal = normal;
         V2.tex = { startS, startT };

         
         switch (plane) {
         case PlaneType::XZ:
            V3.position = { x + facetWidth, y, z + facetDepth };
            break;
         case PlaneType::XZ_Flipped:
            V3.position = { x - facetWidth, y, z + facetDepth };
            break;
         case PlaneType::XY:
            V3.position = { x + facetWidth, y - facetDepth, z };
            break;
         case PlaneType::XY_Flipped:
            V3.position = { x - facetWidth, y - facetDepth, z };
            break;
         case PlaneType::YZ:
            V3.position = { x, y - facetDepth, z - facetWidth};
            break;
         case PlaneType::YZ_Flipped:
            V3.position = { x, y - facetDepth, z + facetWidth };
            break;
         }
         V3.color = color;
         V3.normal = normal;
         V3.tex = { endS, startT };

         switch (plane) {
         case PlaneType::XZ:
            V4.position = { x + facetWidth, y, z };
            break;
         case PlaneType::XZ_Flipped:
            V4.position = { x - facetWidth, y, z };
            break;
         case PlaneType::XY:
            V4.position = { x + facetWidth, y, z };
            break;
         case PlaneType::XY_Flipped:
            V4.position = { x - facetWidth, y, z };
            break;
         case PlaneType::YZ:
            V4.position = { x, y, z - facetWidth };
            break;
         case PlaneType::YZ_Flipped:
            V4.position = { x, y, z + facetWidth };
            break;
         }
         V4.color = color;
         V4.normal = normal;
         V4.tex = { endS, endT };

         meshToFill->AddVertex(V1);
         meshToFill->AddVertex(V2);
         meshToFill->AddVertex(V3);
         meshToFill->AddVertex(V1);
         meshToFill->AddVertex(V3);
         meshToFill->AddVertex(V4);

         startS = endS;
         if (startS >= textureWidthRepeat) startS = 0;
         
         switch (plane) {
         case PlaneType::XZ:
            x += facetWidth;
            break;
         case PlaneType::XZ_Flipped:
            x -= facetWidth;
            break;
         case PlaneType::XY:
            x += facetWidth;
            break;
         case PlaneType::XY_Flipped:
            x -= facetWidth;
            break;
         case PlaneType::YZ:
            z -= facetWidth;
            break;
         case PlaneType::YZ_Flipped:
            z += facetWidth;
            break;
         }
      } // Next col
      startT -= tDelta;
      if (startT < 0) startT = 0;
      
      switch (plane) {
      case PlaneType::XZ:
      case PlaneType::XZ_Flipped:
         z += facetDepth;
         break;
      case PlaneType::XY:
      case PlaneType::XY_Flipped:
      case PlaneType::YZ:
      case PlaneType::YZ_Flipped:
         y -= facetDepth;
         break;
      }
   } // Next row
}

void Generate::NormalizedTexturedFlatMesh(
   PolygonMesh* meshToFill,
   float width, float depth, int widthFacetCount, int depthFacetCount, 
   RGBA color, float textureWidthRepeat, float textureDepthRepeat)
{
   VertexPCNT V1, V2, V3, V4;
   // Each facet is in the XZ plane:
   // V1 V4   V1 has tex coord (startS, endT)
   // +--+    V2 has tex coord (startS, startT)
   // |\ |    V3 has tex coord (endS, startT)
   // | \|    V4 has tex coord (endS, endT)
   // +--+
   // V2 V3
   float halfWidth = width / 2;
   float halfDepth = depth / 2;
   float facetWidth = width / widthFacetCount;
   float facetDepth = depth / depthFacetCount;
   float sDelta = textureWidthRepeat / widthFacetCount;
   float tDelta = textureDepthRepeat / depthFacetCount;
   float startS, startT, endS, endT = textureDepthRepeat;
   float x, y = 0, z = -halfDepth;
   startT = endT - tDelta;
   for (int row = 1; row <= depthFacetCount; ++row) {
      x = -halfWidth;
      startS = 0;
      endT = startT + tDelta;
      for (int col = 1; col <= widthFacetCount; ++col) {
         endS = startS + sDelta;
         if (endS > textureWidthRepeat) endS = textureWidthRepeat;
         V1.position = { x, y, z };
         V1.color = color;
         V1.normal = { 0, 1, 0 };
         V1.tex = { startS, endT };

         V2.position = { x, y, z + facetDepth };
         V2.color = color;
         V2.normal = { 0, 1, 0 };
         V2.tex = { startS, startT };

         V3.position = { x + facetWidth, y, z + facetDepth };
         V3.color = color;
         V3.normal = { 0, 1, 0 };
         V3.tex = { endS, startT };

         V4.position = { x + facetWidth, y, z };
         V4.color = color;
         V4.normal = { 0, 1, 0 };
         V4.tex = { endS, endT };

         meshToFill->AddVertex(V1);
         meshToFill->AddVertex(V2);
         meshToFill->AddVertex(V3);
         meshToFill->AddVertex(V1);
         meshToFill->AddVertex(V3);
         meshToFill->AddVertex(V4);

         startS = endS;
         if (startS >= textureWidthRepeat) startS = 0;
         x += facetWidth;
      } // Next col
      startT -= tDelta;
      if (startT < 0) startT = 0;
      z += facetDepth;
   } // Next row
}

OpenGLGraphicsObject* Generate::NormalizedTexturedFlatSurface(float width, float depth, int widthFacetCount, int depthFacetCount, RGBA color, float textureWidthRepeat, float textureDepthRepeat)
{
   auto flatSurface = new OpenGLGraphicsObject();
   flatSurface->vertexStrategy = new OpenGLVertexPCNTStrategy();
   auto vertexStrategy = (OpenGLVertexPCNTStrategy*)flatSurface->vertexStrategy;
   auto mesh = new PolygonMesh();
   Generate::NormalizedTexturedFlatMesh(
      mesh,
      width, depth, widthFacetCount, depthFacetCount, color, 
      textureWidthRepeat, textureDepthRepeat);
   vertexStrategy->SetMesh(mesh);
   return flatSurface;
}

void Generate::NormalizedTexturedSphereMesh(
   PolygonMesh* meshToFill, 
   float radius, int slices, int stacks, 
   RGBA color, SphereShadingType shadingType)
{
   float sliceStep = 360.0f / slices;
   float stackStep = 180.0f / stacks;
   float phi = stackStep;
   float rho = radius;
   float theta, sinTheta, cosTheta, cosPhi, sinPhi, thetaRad, phiRad;
   VertexPCNT V1, V2, V3, V4;
   glm::vec3 VA, VB, VC, VD;

   // Texture variables
   float tHeight = 1.0f / stacks;
   float tWidth = 1.0f / slices;
   float s = 0.0f, t = 1.0f - tHeight;

   // The top pole is composed of triangles.
   //        V1
   //       / \
	//      /   \
	//    V2-----V3
   // Generate top vertices
   for (theta = 0; theta < 360.0f; theta += sliceStep) {
      // Vertex A is the north pole
      V1.position = { 0.0f, radius, 0.0f };
      VA = glm::vec3(V1.position.x, V1.position.y, V1.position.z);
      V1.color = { color.red, color.green, color.blue, color.alpha };
      V1.normal = { 0, 0, 0 };
      V1.tex = { s, 1.0f };

      thetaRad = glm::radians(theta);
      phiRad = glm::radians(phi);
      sinTheta = sinf(thetaRad);
      sinPhi = sinf(phiRad);
      cosPhi = cosf(phiRad);
      cosTheta = cosf(thetaRad);
      V2.position = { rho * sinTheta * sinPhi, rho * cosPhi, rho * cosTheta * sinPhi };
      VB = glm::vec3(V2.position.x, V2.position.y, V2.position.z);
      V2.color = { color.red, color.green, color.blue, color.alpha };
      V2.normal = { 0, 0, 0 };
      V2.tex = { s, t };

      thetaRad = glm::radians(theta + sliceStep);
      sinTheta = sinf(thetaRad);
      cosTheta = cosf(thetaRad);
      V3.position = { rho * sinTheta * sinPhi, V2.position.y, rho * cosTheta * sinPhi };
      VC = glm::vec3(V3.position.x, V3.position.y, V3.position.z);
      V3.color = { color.red, color.green, color.blue, color.alpha };
      V3.normal = { 0, 0, 0 };
      V3.tex = { s + tWidth, t };

      if (shadingType == SphereShadingType::Flat_Shading) { // Flat shading
         glm::vec3 AB = glm::normalize(VB - VA);
         glm::vec3 AC = glm::normalize(VC - VA);
         glm::vec3 NA = glm::cross(AB, AC);
         V1.normal = { NA.x, NA.y, NA.z };

         glm::vec3 BC = glm::normalize(VC - VB);
         glm::vec3 BA = glm::normalize(VA - VB);
         glm::vec3 NB = glm::cross(BC, BA);
         V2.normal = { NB.x, NB.y, NB.z };

         glm::vec3 CA = glm::normalize(VA - VC);
         glm::vec3 CB = glm::normalize(VB - VC);
         glm::vec3 NC = glm::cross(CA, CB);
         V3.normal = { NC.x, NC.y, NC.z };
      }
      else { // Smooth shading (Use the normalized position vectors as the normal)
         glm::vec3 NA = glm::normalize(VA);
         V1.normal = { NA.x, NA.y, NA.z };

         glm::vec3 NB = glm::normalize(VB);
         V2.normal = { NB.x, NB.y, NB.z };

         glm::vec3 NC = glm::normalize(VC);
         V3.normal = { NC.x, NC.y, NC.z };
      }

      meshToFill->AddVertex(V1);
      meshToFill->AddVertex(V2);
      meshToFill->AddVertex(V3);
      s += tWidth;
   } // Top vertices

   s = 0;
   t = 1.0f - tHeight;
   // The middle facets have 4 vertices
   // V1--V4
   // |\  |
   // | \ |
   // |  \|
   // V2--V3
   float phiUp = phi;
   float phiDown = phi + stackStep;
   // Generate the middle
   const int MiddleStackCount = stacks - 2; // Subtract top and bottom stack
   for (int stack = 0; stack < MiddleStackCount; stack++) {
      for (theta = 0; theta < 360.0f; theta += sliceStep) {
         // V1
         thetaRad = glm::radians(theta);
         sinTheta = sinf(thetaRad);
         cosTheta = cos(thetaRad);
         phiRad = glm::radians(phiUp);
         sinPhi = sinf(phiRad);
         cosPhi = cosf(phiRad);
         V1.position = { rho * sinTheta * sinPhi, rho * cosPhi, rho * cosTheta * sinPhi };
         VA = glm::vec3(V1.position.x, V1.position.y, V1.position.z);
         V1.color = { color.red, color.green, color.blue, color.alpha };
         V1.tex = { s, t };
         // V2
         phiRad = glm::radians(phiDown);
         sinPhi = sinf(phiRad);
         cosPhi = cosf(phiRad);
         V2.position = { rho * sinTheta * sinPhi, rho * cosPhi, rho * cosTheta * sinPhi };
         VB = glm::vec3(V2.position.x, V2.position.y, V2.position.z);
         V2.color = { color.red, color.green, color.blue, color.alpha };
         V2.tex = { s, t - tHeight };
         // V3
         thetaRad = glm::radians(theta + sliceStep);
         sinTheta = sinf(thetaRad);
         cosTheta = cos(thetaRad);
         V3.position = { rho * sinTheta * sinPhi, V2.position.y, rho * cosTheta * sinPhi };
         VC = glm::vec3(V3.position.x, V3.position.y, V3.position.z);
         V3.color = { color.red, color.green, color.blue, color.alpha };
         V3.tex = { s + tWidth, t - tHeight };
         // V4
         phiRad = glm::radians(phiUp);
         sinPhi = sinf(phiRad);
         V4.position = { rho * sinTheta * sinPhi, V1.position.y, rho * cosTheta * sinPhi };
         VD = glm::vec3(V4.position.x, V4.position.y, V4.position.z);
         V4.color = { color.red, color.green, color.blue, color.alpha };
         V4.tex = { s + tWidth, t };

         // V1--V4
         // |\  |
         // | \ |
         // |  \|
         // V2--V3
         if (shadingType == SphereShadingType::Flat_Shading) {
            glm::vec3 AB = glm::normalize(VB - VA);
            glm::vec3 AC = glm::normalize(VC - VA);
            glm::vec3 NA = glm::cross(AB, AC);
            V1.normal = { NA.x, NA.y, NA.z };

            glm::vec3 BC = glm::normalize(VC - VB);
            glm::vec3 BA = glm::normalize(VA - VB);
            glm::vec3 NB = glm::cross(BC, BA);
            V2.normal = { NB.x, NB.y, NB.z };

            glm::vec3 CA = glm::normalize(VA - VC);
            glm::vec3 CB = glm::normalize(VB - VC);
            glm::vec3 NC = glm::cross(CA, CB);
            V3.normal = { NC.x, NC.y, NC.z };

            glm::vec3 AD = glm::normalize(VD - VA);
            glm::vec3 ND = glm::cross(AC, AD);
            V4.normal = { ND.x, ND.y, ND.z };
         }
         else { // Use the normalized position vectors as the normal
            glm::vec3 NA = glm::normalize(VA);
            V1.normal = { NA.x, NA.y, NA.z };

            glm::vec3 NB = glm::normalize(VB);
            V2.normal = { NB.x, NB.y, NB.z };

            glm::vec3 NC = glm::normalize(VC);
            V3.normal = { NC.x, NC.y, NC.z };

            glm::vec3 ND = glm::normalize(VD);
            V4.normal = { ND.x, ND.y, ND.z };
         }

         meshToFill->AddVertex(V1);
         meshToFill->AddVertex(V2);
         meshToFill->AddVertex(V3);

         meshToFill->AddVertex(V1);
         meshToFill->AddVertex(V3);
         meshToFill->AddVertex(V4);
         s += tWidth;
      }
      phiUp = phiDown;
      phiDown = phiUp + stackStep;
      t -= tHeight;
   }
   s = 0.0f;
   // The bottom pole
   //  V1---V3
   //   \   /
   //    \ /
   //     V2
   phi = phiUp;
   for (theta = 0; theta < 360.0f; theta += sliceStep) {
      // V1
      thetaRad = glm::radians(theta);
      sinTheta = sinf(thetaRad);
      cosTheta = cosf(thetaRad);
      phiRad = glm::radians(phi);
      sinPhi = sinf(phiRad);
      cosPhi = cosf(phiRad);
      V1.position = { rho * sinTheta * sinPhi, rho * cosPhi, rho * cosTheta * sinPhi };
      VA = glm::vec3(V1.position.x, V1.position.y, V1.position.z);
      V1.color = { color.red, color.green, color.blue, color.alpha };
      V1.normal = { 0, 0, 0 };
      V1.tex = { s, t };
      // V2
      V2.position = { 0, -radius, 0 };
      VB = glm::vec3(V2.position.x, V2.position.y, V2.position.z);
      V2.color = { color.red, color.green, color.blue, color.alpha };
      V2.normal = { 0, 0, 0 };
      V2.tex = { s, 0.0f };
      // V3
      thetaRad = glm::radians(theta + sliceStep);
      sinTheta = sinf(thetaRad);
      cosTheta = cos(thetaRad);
      V3.position = { rho * sinTheta * sinPhi, V1.position.y, rho * cosTheta * sinPhi };
      VC = glm::vec3(V3.position.x, V3.position.y, V3.position.z);
      V3.color = { color.red, color.green, color.blue, color.alpha };
      V3.normal = { 0, 0, 0 };
      V3.tex = { s + tWidth, t };

      if (shadingType == SphereShadingType::Flat_Shading) {
         glm::vec3 AB = glm::normalize(VB - VA);
         glm::vec3 AC = glm::normalize(VC - VA);
         glm::vec3 NA = glm::cross(AB, AC);
         V1.normal = { NA.x, NA.y, NA.z };

         glm::vec3 BC = glm::normalize(VC - VB);
         glm::vec3 BA = glm::normalize(VA - VB);
         glm::vec3 NB = glm::cross(BC, BA);
         V2.normal = { NB.x, NB.y, NB.z };

         glm::vec3 CA = glm::normalize(VA - VC);
         glm::vec3 CB = glm::normalize(VB - VC);
         glm::vec3 NC = glm::cross(CA, CB);
         V3.normal = { NC.x, NC.y, NC.z };
      }
      else { // Use the normalized position vectors as the normal
         glm::vec3 NA = glm::normalize(VA);
         V1.normal = { NA.x, NA.y, NA.z };

         glm::vec3 NB = glm::normalize(VB);
         V2.normal = { NB.x, NB.y, NB.z };

         glm::vec3 NC = glm::normalize(VC);
         V3.normal = { NC.x, NC.y, NC.z };
      }

      meshToFill->AddVertex(V1);
      meshToFill->AddVertex(V2);
      meshToFill->AddVertex(V3);

      s += tWidth;
   }
} // NormalizedTexturedSphereMesh

OpenGLGraphicsObject* Generate::Sphere(
   float radius, int slices, int stacks, 
   RGBA color, SphereShadingType shadingType)
{
   auto sphere = new OpenGLGraphicsObject();
   sphere->vertexStrategy = new OpenGLVertexPCNTStrategy();
   auto vertexStrategy = (OpenGLVertexPCNTStrategy*)sphere->vertexStrategy;
   auto mesh = new PolygonMesh();
   Generate::NormalizedTexturedSphereMesh(
      mesh,
      radius, slices, stacks, color,
      shadingType);
   vertexStrategy->SetMesh(mesh);
   return sphere;
} // Sphere
