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

void BaseCamera::SetupProjectionAndView(float aspectRatio)
{
   _aspectRatio = aspectRatio;
   _projection = glm::perspective(
      glm::radians(fieldOfView),
      _aspectRatio,
      nearPlane,
      farPlane
   );
   _view = glm::lookAt(
      frame.GetPosition(),
      target,
      frame.GetYAxis()
   );
}
