#include "BaseCamera.h"
#include <glm/gtc/matrix_transform.hpp>

BaseCamera::BaseCamera() : 
   fieldOfView(60.0f), _aspectRatio(1.0f), 
   nearPlane(0.1f), farPlane(50.0f), frame(), 
   target({ 0.0f, 0.0f, 0.0f }), 
   _projection(1.0f), _view(1.0f),
   _state(CameraState::NotMoving), euler({0, -90.0f, 0})
{
   frame.SetPosition(0.0f, 0.0f, 5.0f);
}

void BaseCamera::Update(double elapsedSeconds)
{
   switch (_state) {
      case CameraState::NotMoving:
         break;
      case CameraState::MovingForward: {
         auto forward = -frame.GetZAxis();
         forward *= (2.0 * elapsedSeconds);
         frame.Move(forward);
         break;
      }
      case CameraState::MovingBackward: {
         auto backward = frame.GetZAxis();
         backward *= (2.0 * elapsedSeconds);
         frame.Move(backward);
         break;
      }
      case CameraState::MovingUp: {
         auto up = frame.GetYAxis();
         up *= (2.0 * elapsedSeconds);
         frame.Move(up);
         break;
      }
      case CameraState::MovingDown: {
         auto down = -frame.GetYAxis();
         down *= (2.0 * elapsedSeconds);
         frame.Move(down);
         break;
      }
      case CameraState::TurningRight: {
         auto turnAngle = -90.0 * elapsedSeconds;
         frame.Rotate((float)turnAngle, frame.GetYAxis());
         break;
      }
      case CameraState::TurningLeft: {
         auto turnAngle = 90.0 * elapsedSeconds;
         frame.Rotate((float)turnAngle, frame.GetYAxis());
         break;
      }
      case CameraState::MovingRight: {
         auto right = frame.GetXAxis();
         right *= (2.0 * elapsedSeconds);
         frame.Move(right);
         break;
      }
      case CameraState::MovingLeft: {
         auto left = -frame.GetXAxis();
         left *= (2.0 * elapsedSeconds);
         frame.Move(left);
         break;
      }
   }
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

void BaseCamera::SetupViewingFrustum(float depth)
{
   auto fieldOfViewRadians = glm::radians(fieldOfView);
   auto frontHeight = tanf(fieldOfViewRadians) * nearPlane * 2;
   auto backHeight = tanf(fieldOfViewRadians)* depth * 2;
   auto frontWidth = _aspectRatio * frontHeight;
   auto backWidth = _aspectRatio * backHeight;
   viewingFrustum.Set(frontWidth, frontHeight, backWidth, backHeight, depth);
}

void BaseCamera::OrientViewingFrustum()
{
   viewingFrustum.frame = frame;
   viewingFrustum.frame.Rotate(180.0f, viewingFrustum.frame.GetYAxis());
   viewingFrustum.Create();
}
