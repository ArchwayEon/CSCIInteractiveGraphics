#pragma once
#ifndef HIGH_RESOLUTION_TIMER
#define HIGH_RESOLUTION_TIMER
#include "AbstractTimer.h"
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std::chrono;

class HighResolutionTimer :
   public AbstractTimer
{
protected:
   high_resolution_clock::time_point _start, _end;

public:
   HighResolutionTimer();
   void StartTiming();
   double GetElapsedTimeInSeconds();
};

#endif

