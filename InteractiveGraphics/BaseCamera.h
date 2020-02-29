#pragma once
#ifndef ABSTRACT_CAMERA
#define ABSTRACT_CAMERA
#include "ReferenceFrame.h"
#include <glm\glm.hpp>

class BaseCamera
{
private:
   glm::mat4 _projection, _view;
   float _aspectRatio;

public:
   float fieldOfView, nearPlane, farPlane;
   ReferenceFrame frame;
   glm::vec3 target;

public:
   BaseCamera();
   ~BaseCamera() {}

   virtual void Update() {};
   virtual const glm::mat4& GetProjection() const { return _projection; }
   virtual const glm::mat4& GetView() const { return _view; }
   virtual void SetupProjectionAndView(float aspectRatio);
};

#endif

