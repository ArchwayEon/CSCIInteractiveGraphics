#include "BaseCamera.h"
#include <glm/gtc/matrix_transform.hpp>

BaseCamera::BaseCamera() : 
   fieldOfView(60.0f), _aspectRatio(1.0f), 
   nearPlane(0.1f), farPlane(50.0f), frame(), 
   target({ 0.0f, 0.0f, 0.0f }), 
   _projection(1.0f), _view(1.0f)
{
   frame.SetPosition(0.0f, 0.0f, 5.0f);
}

void BaseCamera::SetupLookingForward()
{
   glm::vec3 position = frame.GetPosition();
   glm::vec3 forward = frame.orientation[2];
   forward = -forward;
   target = position + forward;
}

void BaseCamera::SetupProjectionAndView(float aspectRatio)
{
   _aspectRatio = aspectRatio;
   _projection = glm::perspective(
      glm::radians(fieldOfView),
      _aspectRatio,
      nearPlane,
      farPlane
   );
   glm::vec3 position = frame.GetPosition();
   _view = glm::lookAt(
      position,
      target,
      frame.GetYAxis()
   );
}
