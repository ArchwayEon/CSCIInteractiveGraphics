#include "AbstractGraphicsWindow.h"

AbstractGraphicsWindow::AbstractGraphicsWindow(string title, int width, int height) :
   _title(title), _width(width), _height(height), backgroundColor({ 0.0f, 0.0f, 0.0f }),
   _firstMouse(false), _lastMouseX(0), _lastMouseY(0), spherical({90.0f, 0, 0})
{
}

AbstractGraphicsWindow::~AbstractGraphicsWindow()
{
}

void AbstractGraphicsWindow::ProcessMouse(double mouseX, double mouseY)
{
   if (_firstMouse){
      _lastMouseX = mouseX;
      _lastMouseY = mouseY;
      _firstMouse = false;
   }

   double xoffset = _lastMouseX - mouseX;
   double yoffset = _lastMouseY - mouseY;
   _lastMouseX = mouseX;
   _lastMouseY = mouseY;

   double sensitivity = 0.05; // smaller is less sensitive
   xoffset *= sensitivity;
   yoffset *= sensitivity;

   spherical.theta += (float)xoffset;
   spherical.phi += (float)yoffset;

   if (spherical.phi > 179.0f) spherical.phi = 179.0f;
   if (spherical.phi < 1.0f) spherical.phi = 1.0f;
}
