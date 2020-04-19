#include "ViewingFrustum.h"

ViewingFrustum::ViewingFrustum()
{
   Set(0.5f, 0.5f, 1.0f, 1.0f, 1.0f);
}

void ViewingFrustum::Set(float frontWidth, float frontHeight, float backWidth, float backHeight, float depth)
{
   _frontWidth = frontWidth;
   _frontHeight = frontHeight;
   _backWidth = backWidth;
   _backHeight = backHeight;
   _depth = depth;
   Create();
}

void ViewingFrustum::Create()
{
   auto halfFrontWidth = _frontWidth / 2;
   auto halfFrontHeight = _frontHeight / 2;
   auto halfBackWidth = _backWidth  / 2;
   auto halfBackHeight = _backHeight / 2;

   glm::vec3 ulf = { halfFrontWidth, halfFrontHeight, 0 };
   glm::vec3 llf = { halfFrontWidth, -halfFrontHeight, 0 };
   glm::vec3 lrf = { -halfFrontWidth, -halfFrontHeight, 0 };
   glm::vec3 urf = { -halfFrontWidth,  halfFrontHeight, 0 };
   glm::vec3 ulb = { halfBackWidth,  halfBackHeight, _depth };
   glm::vec3 llb = { halfBackWidth, -halfBackHeight, _depth };
   glm::vec3 lrb = { -halfBackWidth, -halfBackHeight, _depth };
   glm::vec3 urb = { -halfBackWidth,  halfBackHeight, _depth };

   auto F1 = frame.orientation * ulf;
   auto F2 = frame.orientation * 
}

bool ViewingFrustum::HasSphereInside(const BoundingSphere& sphere)
{
   return false;
}

bool ViewingFrustum::HasPointInside(glm::vec3 point)
{
   return false;
}
