#pragma once
#ifndef ABSTRACT_TIMER
#define ABSTRACT_TIMER

class AbstractTimer
{
public:
   AbstractTimer();
   virtual ~AbstractTimer();

   virtual void StartTiming() = 0;
   virtual double GetElapsedTimeInSeconds() = 0;
};

#endif

