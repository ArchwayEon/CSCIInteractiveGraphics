#pragma once
#ifndef VIEWING_FRUSTUM
#define VIEWING_FRUSTUM
#include "GeometricPlane.h"
#include "ReferenceFrame.h"

class ViewingFrustum
{
protected:
   float _frontWidth, _frontHeight, _backWidth, _backHeight;
   float _depth;
   GeometricPlane _planes[6];

public:
   ReferenceFrame frame;

public:
   ViewingFrustum();
   void Set(float frontWidth, float frontHeight, float backWidth, float backHeight, float depth);
   void Create();
   bool HasSphereInside(const BoundingSphere& sphere);
   bool HasPointInside(glm::vec3 point);
};

#endif

