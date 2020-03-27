#pragma once

#ifndef GENERATE
#define GENERATE
#include "OpenGLIndexedGraphicsObject.h"
#include "OpenGLGraphicsObject.h"
#include "GraphicsStructures.h"


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
   static OpenGLGraphicsObject* Axis(float xLength=1, float yLength=1, float zLength=1);
   static OpenGLGraphicsObject* TexturedCuboid(float width, float depth, float height, RGBA color, float maxS = 1, float maxT = 1);
   static OpenGLGraphicsObject* NormalizedTexturedCuboid(float width, float depth, float height, RGBA color, float maxS=1, float maxT=1);
};

#endif

