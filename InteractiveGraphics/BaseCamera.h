#pragma once
#ifndef ABSTRACT_CAMERA
#define ABSTRACT_CAMERA
#include "ReferenceFrame.h"
#include <glm\glm.hpp>
#include "ViewingFrustum.h"

class BaseCamera
{
public:
   enum class CameraState {
      NotMoving, MovingForward, MovingBackward, MovingUp, MovingDown,
      TurningRight, TurningLeft,
      MovingRight, MovingLeft
   };

protected:
   glm::mat4 _projection, _view;
   float _aspectRatio;
   CameraState _state;
   SphericalCoordinate euler;

public:
   float fieldOfView, nearPlane, farPlane;
   ReferenceFrame frame;
   ViewingFrustum viewingFrustum;
   glm::vec3 target;

public:
   BaseCamera();
   ~BaseCamera() {}

   virtual void SetState(CameraState state) { _state = state; }
   virtual void Update(double elapsedSeconds);
   virtual const glm::mat4& GetProjection() const { return _projection; }
   virtual const glm::mat4& GetView() const { return _view; }
   virtual void SetupLookingForward();
   virtual void SetupProjectionAndView(float aspectRatio);
   virtual void SetupViewingFrustum(float depth);
   virtual void OrientViewingFrustum();
};

#endif

