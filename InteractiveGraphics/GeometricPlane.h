#pragma once
#ifndef GEOMETRIC_PLANE
#define GEOMETRIC_PLANE
#include <glm\glm.hpp>
#include "BoundingSphere.h"

class GeometricPlane
{
protected:
   glm::vec3 N;
   float d;

public:
   GeometricPlane() {
      N = { 0, 1, 0 };
      d = 0;
   }
   void Set(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
   void Set(glm::vec3 normal, glm::vec3 p);
   bool IsPointInFront(glm::vec3 p);
   bool IsSphereInFront(const BoundingSphere& sphere);
};

#endif

