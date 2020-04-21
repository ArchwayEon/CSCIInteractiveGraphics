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
   const int FRONT = 0;
   const int BACK = 1;
   const int LEFT = 2;
   const int RIGHT = 3;
   const int TOP = 4;
   const int BOTTOM = 5;

public:
   ViewingFrustum();
   void Set(float frontWidth, float frontHeight, float backWidth, float backHeight, float depth);
   void Create();
   bool HasSphereInside(const BoundingSphere& sphere);
   bool HasPointInside(glm::vec3 point);
};

#endif

