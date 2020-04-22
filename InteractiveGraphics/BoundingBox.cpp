#include "BoundingBox.h"
#include "ReferenceFrame.h"

BoundingBox::BoundingBox() :
   width(1.0f), height(1.0f), depth(1.0f), frame(nullptr)
{
}

BoundingBox::BoundingBox(float width, float height, float depth) :
   width(width), height(height), depth(depth), frame(nullptr)
{
}

void BoundingBox::Set(float width, float height, float depth)
{
   this->width = width;
   this->height = height;
   this->depth = depth;
}

bool BoundingBox::OverlapsWith(const BoundingBox& other)
{
   glm::vec3 xAxis = frame->orientation[0];
   MinMax b1 = GetMinMaxProjection(xAxis);
   MinMax b2 = other.GetMinMaxProjection(xAxis);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   glm::vec3 xAxisOther = other.frame->orientation[0];
   b1 = GetMinMaxProjection(xAxisOther);
   b2 = other.GetMinMaxProjection(xAxisOther);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   glm::vec3 yAxis = frame->orientation[1];
   b1 = GetMinMaxProjection(yAxis);
   b2 = other.GetMinMaxProjection(yAxis);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   glm::vec3 yAxisOther = other.frame->orientation[1];
   b1 = GetMinMaxProjection(yAxisOther);
   b2 = other.GetMinMaxProjection(yAxisOther);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   glm::vec3 zAxis = frame->orientation[2];
   b1 = GetMinMaxProjection(zAxis);
   b2 = other.GetMinMaxProjection(zAxis);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   glm::vec3 zAxisOther = other.frame->orientation[2];
   b1 = GetMinMaxProjection(zAxisOther);
   b2 = other.GetMinMaxProjection(zAxisOther);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   glm::vec3 edge = glm::normalize(glm::cross(xAxis, xAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(xAxis, yAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(xAxis, zAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(yAxis, xAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(yAxis, yAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(yAxis, zAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(zAxis, xAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(zAxis, yAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   edge = glm::normalize(glm::cross(zAxis, zAxisOther));
   b1 = GetMinMaxProjection(edge);
   b2 = other.GetMinMaxProjection(edge);
   if (b1.max < b2.min || b2.max < b1.min) return false;

   return true;
}

MinMax BoundingBox::GetMinMaxProjection(const glm::vec3& axis) const
{
   float halfWidth = width / 2;
   float halfHeight = height / 2;
   float halfDepth = depth / 2;
   glm::vec3 v[8];
   // Front Face
   v[0] = frame->orientation * glm::vec4(-halfWidth, halfHeight, halfDepth, 1.0f);
   v[1] = frame->orientation * glm::vec4(-halfWidth, -halfHeight, halfDepth, 1.0f);
   v[2] = frame->orientation * glm::vec4(halfWidth, -halfHeight, halfDepth, 1.0f);
   v[3] = frame->orientation * glm::vec4(halfWidth, halfHeight, halfDepth, 1.0f);
   // Back Face
   v[4] = frame->orientation * glm::vec4(-halfWidth, halfHeight, -halfDepth, 1.0f);
   v[5] = frame->orientation * glm::vec4(-halfWidth, -halfHeight, -halfDepth, 1.0f);
   v[6] = frame->orientation * glm::vec4(halfWidth, -halfHeight, -halfDepth, 1.0f);
   v[7] = frame->orientation * glm::vec4(halfWidth, halfHeight, -halfDepth, 1.0f);

   MinMax m;
   m.min = m.max = glm::dot(v[0], axis);
   float val;
   for (auto i = 1; i < 8; i++) {
      val = glm::dot(v[i], axis);
      if (val < m.min) {
         m.min = val;
      }
      if (val > m.max) {
         m.max = val;
      }
   }
   return m;
}
