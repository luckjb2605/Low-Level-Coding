#pragma once
#define _USE_MATH_DEFINES
#include <SDL2/SDL.h>
#include <cmath>
#include "constants.h"

class Circle
{
private:
  int radius;
  Point center;
  Point points[NUM_OF_POINTS];
public:
  Circle(Point center, int radius);
  int   GetRadius() const;
  Point GetCenter() const;
  Point GetPoint(int index) const;
  void ComputePoints();
};