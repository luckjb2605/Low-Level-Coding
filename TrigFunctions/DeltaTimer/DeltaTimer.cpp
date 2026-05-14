#include "DeltaTimer/DeltaTimer.h"

DeltaTimer::DeltaTimer()
{
  now = SDL_GetPerformanceCounter();
  last = now;
  start = now;
}

float DeltaTimer::Update()
{
  last = now;
  now = SDL_GetPerformanceCounter();
  return (float)(now-last)
    /SDL_GetPerformanceFrequency();
}

float DeltaTimer::Elapsed()
{
  return (float)(now-start)
    /SDL_GetPerformanceFrequency();
}