#include "ReferenceFrame.h"
#include <glm/gtc/matrix_transform.hpp>

void ReferenceFrame::Rotate(float degrees, const glm::vec3& axis)
{
   orientation = glm::rotate(orientation, glm::radians(degrees), axis);
}

void ReferenceFrame::RotateWorld(float degrees, const glm::vec3& axis)
{
   glm::mat4 mat(1.0f);
   mat = glm::rotate(mat, glm::radians(degrees), axis);
   orientation = mat * orientation;
}

void ReferenceFrame::Scale(float ratio)
{
   glm::vec3 sv(ratio, ratio, ratio);
   orientation = glm::scale(orientation, sv);
}

void ReferenceFrame::Move(const glm::vec3& vector)
{
   glm::mat4 translateMat(0.0f);
   translateMat[3] = glm::vec4(vector, 0.0f);
   this->orientation += translateMat;
}

void ReferenceFrame::PointAt(float x, float y, float z)
{
   PointAt({ x, y, z });
}

void ReferenceFrame::PointAt(const glm::vec3& point)
{
   glm::vec3 position = GetPosition();
   glm::vec3 forward = glm::normalize(position - point);
   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
   glm::vec3 cameraRight = glm::normalize(glm::cross(up, forward));
   glm::vec3 cameraUp = glm::cross(forward, cameraRight);
   this->orientation[0] = glm::vec4(cameraRight, 0.0f);
   this->orientation[1] = glm::vec4(cameraUp, 0.0f);
   this->orientation[2] = glm::vec4(forward, 0.0f);
}

void ReferenceFrame::SetFromSphericalCoordinates(SphericalCoordinate spherical)
{
   glm::vec3 forward;
   forward.x = sin(glm::radians(spherical.theta)) * sin(glm::radians(spherical.phi));
   forward.y = cos(glm::radians(spherical.phi));
   forward.z = cos(glm::radians(spherical.theta)) * sin(glm::radians(spherical.phi));

   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
   glm::vec3 cameraRight = glm::normalize(glm::cross(up, forward));
   glm::vec3 cameraUp = glm::cross(forward, cameraRight);
   this->orientation[0] = glm::vec4(cameraRight, 0.0f);
   this->orientation[1] = glm::vec4(cameraUp, 0.0f);
   this->orientation[2] = glm::vec4(forward, 0.0f);
}
