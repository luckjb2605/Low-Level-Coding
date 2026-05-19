#pragma once
#define _USE_MATH_DEFINES
#include <SDL2/SDL.h>
#include "Circle/Circle.h"
#include <cmath>

class ClockHand
{
private:
  Point tail;
  Point head;
public:
  ClockHand(Point tail);
  Point GetTail()  const;
  Point GetHead()  const;
  void Update(
    Circle& circle,
    float angle
  );
};