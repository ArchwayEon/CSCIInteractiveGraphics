#include "GeometricPlane.h"

void GeometricPlane::Set(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
   auto v1 = p2 - p1;
   auto v2 = p3 - p1;
   N = glm::normalize(glm::cross(v1, v2));
   d = -(glm::dot(p1, N));
}

void GeometricPlane::Set(glm::vec3 normal, glm::vec3 p)
{
   N = glm::normalize(normal);
   d = -(glm::dot(p, N));
}

bool GeometricPlane::IsPointInFront(glm::vec3 p)
{
   auto projection = glm::dot(p, N);
   return (projection + d) > 0;
}

bool GeometricPlane::IsSphereInFront(const BoundingSphere& sphere)
{
   auto projection = glm::dot(sphere.position, N);
   return (projection + d + sphere.radius) > 0;
}
