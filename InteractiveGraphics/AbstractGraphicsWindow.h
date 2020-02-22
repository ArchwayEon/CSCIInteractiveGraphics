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

public:
   RGBA backgroundColor;

public:
   AbstractGraphicsWindow(string title, int width=800, int height=600);
   virtual ~AbstractGraphicsWindow();

   virtual bool Create() = 0;
   virtual void SetOnResize() = 0;
   virtual void Show() = 0;
   virtual void ShowMaximized() = 0;
   virtual void Close() = 0;
   virtual bool IsTimeToClose() = 0;
   virtual void SwapBuffers() = 0;
   virtual void Clear() = 0;
   virtual int GetKeyState(int key) = 0;
};

#endif

