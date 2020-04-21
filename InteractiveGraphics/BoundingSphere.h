#pragma once
#ifndef BOUNDING_SPHERE
#define BOUNDING_SPHERE
#include <glm\glm.hpp>

class BoundingSphere
{
public:
   glm::vec3 position;
   float radius;

public:
   bool OverlapsWith(const BoundingSphere& otherSphere);
};
#endif

