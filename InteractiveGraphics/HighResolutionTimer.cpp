#include "HighResolutionTimer.h"

HighResolutionTimer::HighResolutionTimer()
{
   StartTiming();
}

void HighResolutionTimer::StartTiming()
{
   _start = high_resolution_clock::now();
}

double HighResolutionTimer::GetElapsedTimeInSeconds()
{
   _end = high_resolution_clock::now();
   duration<double> timeSpan = 
      duration_cast<duration<double>>(_end - _start);
   _start = high_resolution_clock::now();
   return timeSpan.count();
}
