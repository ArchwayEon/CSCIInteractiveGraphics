#include "AbstractGraphicsWindow.h"

AbstractGraphicsWindow::AbstractGraphicsWindow(string title, int width, int height) :
   _title(title), _width(width), _height(height), backgroundColor({ 0.0f, 0.0f, 0.0f })
{
}

AbstractGraphicsWindow::~AbstractGraphicsWindow()
{
}
