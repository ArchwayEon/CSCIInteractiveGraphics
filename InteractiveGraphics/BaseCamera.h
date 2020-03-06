#pragma once
#ifndef ABSTRACT_CAMERA
#define ABSTRACT_CAMERA
#include "ReferenceFrame.h"
#include <glm\glm.hpp>

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

public:
   float fieldOfView, nearPlane, farPlane;
   ReferenceFrame frame;
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
};

#endif

