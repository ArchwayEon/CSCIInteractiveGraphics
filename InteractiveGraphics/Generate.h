#pragma once

#ifndef GENERATE
#define GENERATE
#include "OpenGLIndexedGraphicsObject.h"
#include "OpenGLGraphicsObject.h"
#include "GraphicsStructures.h"

class AbstractMesh;

class Generate
{
public:
   static OpenGLGraphicsObject* FlatSurface(float width, float depth, RGBA color);
   static OpenGLGraphicsObject* TexturedFlatSurface(float width, float depth, RGBA color, float maxS, float maxT);
   static OpenGLGraphicsObject* NormalizedTexturedFlatSurface(float width, float depth, RGBA color, float maxS, float maxT);
   static OpenGLGraphicsObject* Cuboid(float width, float depth, float height, RGBA color);
   static OpenGLIndexedGraphicsObject* IndexedFlatSurface(float width, float depth, RGBA color);
   static OpenGLGraphicsObject* TexturedCuboid(float width, float depth, float height, RGBA color);
   static OpenGLGraphicsObject* NormalizedTexturedCuboid(float width, float depth, float height, RGBA color, float maxS=1, float maxT=1);
   static AbstractMesh* NormalizedTexturedFlatMesh(
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static OpenGLGraphicsObject* NormalizedTexturedFlatSurface(
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
};

#endif

