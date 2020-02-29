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

void ReferenceFrame::Move(const glm::vec3& vector)
{
   glm::mat4 translateMat(0.0f);
   translateMat[3] = glm::vec4(vector, 0.0f);
   this->orientation += translateMat;
}
