#pragma once

#define _USE_MATH_DEFINES
#include <stdint.h>
#include <cmath>
#include "constants.h"

// Save circumference
// Draw lines between origin and circumferece points

class Angle
{
public:
  Angle();
  void Update();
private:
  int radius;
  uint32_t color;
  Point circumference[2*M_PI*radius];
};