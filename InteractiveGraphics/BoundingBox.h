#pragma once
#ifndef BOUNDING_BOX
#define BOUNDING_BOX

#include <glm/glm.hpp>

class ReferenceFrame;

struct MinMax {
   float min;
   float max;
};

class BoundingBox
{
public:
   float width, height, depth;
   ReferenceFrame* frame;

public:
   BoundingBox();
   BoundingBox(float width, float height, float depth);

   bool OverlapsWith(const BoundingBox& other);
   MinMax GetMinMaxProjection(const glm::vec3& axis) const;
};

#endif

