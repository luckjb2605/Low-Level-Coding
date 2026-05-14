#pragma once
#include <SDL2/SDL.h>

class DeltaTimer
{
private:
  Uint64 now;
  Uint64 last;
  Uint64 start;
public:
  DeltaTimer();
  float Update();
  float Elapsed();
};