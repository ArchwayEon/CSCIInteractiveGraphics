#pragma once

#ifndef GENERATE
#define GENERATE
#include "OpenGLIndexedGraphicsObject.h"
#include "OpenGLGraphicsObject.h"
#include "GraphicsStructures.h"

template <class T>
class PolygonMesh;

class Generate
{
public:
   static OpenGLGraphicsObject* Axis(float xLength = 1, float yLength = 1, float zLength = 1);
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
      PolygonMesh<VertexPCNT>* meshToFill,
      PlaneType plane, float offst,
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static void NormalizedTexturedFlatMesh(
      PolygonMesh<VertexPCNT>* meshToFill,
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static OpenGLGraphicsObject* NormalizedTexturedFlatSurface(
      float width, float depth, int widthFacetCount, int depthFacetCount,
      RGBA color, float textureWidthRepeat, float textureDepthRepeat);
   static void NormalizedTexturedSphereMesh(
      PolygonMesh<VertexPCNT>* meshToFill,
      float radius, int slices, int stacks,
      RGBA color, SphereShadingType shadingType);
   static OpenGLGraphicsObject* Sphere(
      float radius, int slices, int stacks,
      RGBA color, SphereShadingType shadingType);

   static void NormalizedTexturedCylinderMesh(
      PolygonMesh<VertexPCNT>* meshToFill,
      float radius, float height, int slices, int stacks,
      RGBA color, SphereShadingType shadingType);
   static OpenGLGraphicsObject* Cylinder(
      float radius, float height, int slices, int stacks,
      RGBA color, SphereShadingType shadingType);

   static OpenGLGraphicsObject* Circle(float radius, RGBA color, int steps=10);
   static OpenGLGraphicsObject* Spirograph(float R, float l, float k, RGBA color, 
      float revolutions=1, int steps = 10);

   static OpenGLGraphicsObject* QuadraticBezier(glm::vec3 points[], RGBA color, int steps = 10);
   static OpenGLGraphicsObject* QuadraticBezierM(glm::vec3 points[], RGBA color, int steps = 10);
   static OpenGLGraphicsObject* CubicBezier(glm::vec3 points[], RGBA color, int steps = 10);
   static OpenGLGraphicsObject* CubicBezierM(glm::vec3 points[], RGBA color, int steps = 10);
   static OpenGLGraphicsObject* CubicBezierPatch(glm::vec3 points[][4], RGBA color, int steps = 10);

   static void NormalizedTexturedBezierPatchMesh(
      PolygonMesh<VertexPCNT>* meshToFill,
      glm::vec3 controlPoints[][4],
      RGBA color, float maxS = 1, float maxT = 1, int steps = 10);

};

#endif

