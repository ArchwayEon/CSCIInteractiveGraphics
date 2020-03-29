#pragma once

#ifndef GENERATE
#define GENERATE
#include "OpenGLIndexedGraphicsObject.h"
#include "OpenGLGraphicsObject.h"
#include "GraphicsStructures.h"

class PolygonMesh;

class Generate
{
public:
   static OpenGLGraphicsObject* FlatSurface(
      string type,
      float width, float depth, RGBA color, float maxS, float maxT);
   static OpenGLGraphicsObject* FlatSurface(float width, float depth, RGBA color);
   static OpenGLIndexedGraphicsObject* IndexedFlatSurface(float width, float depth, RGBA color);
   static OpenGLGraphicsObject* TexturedFlatSurface(
      float width, float depth, RGBA color, float maxS, float maxT);
   static OpenGLGraphicsObject* NormalizedTexturedFlatSurface(
      float width, float depth, RGBA color, float maxS, float maxT);

   static OpenGLGraphicsObject* Cuboid(string type, 
      float width, float depth, float height, RGBA color, float maxS = 1, float maxT = 1);
   static OpenGLGraphicsObject* Cuboid(float width, float depth, float height, RGBA color);
   static OpenGLGraphicsObject* TexturedCuboid(float width, float depth, float height, RGBA color, float maxS = 1, float maxT = 1);
   static OpenGLGraphicsObject* NormalizedTexturedCuboid(float width, float depth, float height, RGBA color, float maxS=1, float maxT=1);
   static OpenGLGraphicsObject* NormalizedTexturedMeshedCuboid(
      float width, float depth, float height, RGBA color, 
      int widthFacetCount, int depthFacetCount, int heightFacetCount,
      float maxS = 1, float maxT = 1, float maxSdepth = 1);
   static void NormalizedTexturedFlatMesh(
      PolygonMesh* meshToFill,
      PlaneType plane, float offst,
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static void NormalizedTexturedFlatMesh(
      PolygonMesh* meshToFill,
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static OpenGLGraphicsObject* NormalizedTexturedFlatSurface(
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static void NormalizedTexturedSphereMesh(
      PolygonMesh* meshToFill,
      float radius, int slices, int stacks,
      RGBA color, SphereShadingType shadingType);
   static OpenGLGraphicsObject* Sphere(
      float radius, int slices, int stacks,
      RGBA color, SphereShadingType shadingType);
};

#endif

