#pragma once
#ifndef ABSTRACT_GRAPHCIS_WINDOW
#define ABSTRACT_GRAPHICS_WINDOW

#include <string>
using namespace std;
#include "GraphicsStructures.h"

class AbstractGraphicsWindow
{
protected:
   int _width, _height;
   string _title;
   // Used to track the mouse
   double _lastMouseX, _lastMouseY; 
   bool _firstMouse;

public:
   RGBA backgroundColor;
   // Used to track the Euler angle of the mouse
   SphericalCoordinate spherical;

public:
   AbstractGraphicsWindow(string title, int width=800, int height=600);
   virtual ~AbstractGraphicsWindow();

   virtual void SetTitle(const string& title) {
      _title = title;
   }
   virtual bool Create() = 0;
   virtual void SetOnResize() = 0;
   virtual void SetOnMouseEvent() = 0;
   virtual void Show() = 0;
   virtual void ShowMaximized() = 0;
   virtual void Close() = 0;
   virtual bool IsTimeToClose() = 0;
   virtual void SwapBuffers() = 0;
   virtual void Clear() = 0;
   virtual int GetKeyState(int key) = 0;
   virtual void GetWindowSize() = 0;
   virtual void HideAndCaptureMouseCursor() = 0;
   virtual void ProcessMouse(double mouseX, double mouseY);
   virtual void ResetMouse() {
      _lastMouseX = _width / 2;
      _lastMouseY = _height / 2;
      _firstMouse = true;
   }
   virtual float GetAspectRatio() {
      return _width / (float)_height;
   }
};

#endif

