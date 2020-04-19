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

   glm::vec4 ulf = { halfFrontWidth, halfFrontHeight, 0, 1 };
   glm::vec4 llf = { halfFrontWidth, -halfFrontHeight, 0, 1 };
   glm::vec4 lrf = { -halfFrontWidth, -halfFrontHeight, 0, 1 };
   glm::vec4 urf = { -halfFrontWidth,  halfFrontHeight, 0, 1 };
   glm::vec4 ulb = { halfBackWidth,  halfBackHeight, _depth, 1 };
   glm::vec4 llb = { halfBackWidth, -halfBackHeight, _depth, 1 };
   glm::vec4 lrb = { -halfBackWidth, -halfBackHeight, _depth, 1 };
   glm::vec4 urb = { -halfBackWidth,  halfBackHeight, _depth, 1 };

   auto F1 = frame.orientation * ulf;
   auto F2 = frame.orientation * llf;
   auto F3 = frame.orientation * lrf;
   auto F4 = frame.orientation * urf;

   auto B1 = frame.orientation * ulb;
   auto B2 = frame.orientation * llb;
   auto B3 = frame.orientation * lrb;
   auto B4 = frame.orientation * urb;

   _planes[FRONT].Set(frame.GetZAxis(), F3);
   _planes[BACK].Set(-frame.GetZAxis(), B2);
   _planes[LEFT].Set(F1, F2, B2);
   _planes[RIGHT].Set(B4, B3, F3);
   _planes[TOP].Set(F1, B1, B4);
   _planes[BOTTOM].Set(B2, F2, F3);
}

bool ViewingFrustum::HasSphereInside(const BoundingSphere& sphere)
{
   for (auto i = 0; i < 6; i++) {
      if (!_planes[i].IsSphereInFront(sphere)) {
         return false;
      }
   }
   return true;
}

bool ViewingFrustum::HasPointInside(glm::vec3 point)
{
   for (auto i = 0; i < 6; i++) {
      if (!_planes[i].IsPointInFront(point)) {
         return false;
      }
   }
   return true;
}
