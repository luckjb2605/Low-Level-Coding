#define _USE_MATH_DEFINES
#pragma once

#include <cmath>
#include <stdint.h>
#include <vector>

#include "ClockHand/ClockHand.h"
#include "Circle/Circle.h"
#include "constants.h"

class Projection
{
public:
  Projection(Axis, Circle*, uint32_t color);
  Point    GetCenter() const;
  Point    GetHead()   const;
  uint32_t GetColor()  const;
  void Update(float angle);
  std::vector<Line> GetLink(Point);
private:
  Axis axis;
  Point center;
  uint32_t color;
  Circle* circle;
  Point head;
};