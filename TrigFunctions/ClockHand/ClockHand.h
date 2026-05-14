#pragma once
#include <SDL2/SDL.h>
#include "Circle/Circle.h"

class ClockHand
{
private:
  float angle; //degrees
  Point tail;
  Point head;
public:
  ClockHand();
  Point GetTail()  const;
  Point GetHead()  const;
  float GetAngle() const;
  void Update(Circle circle, float dt);
};