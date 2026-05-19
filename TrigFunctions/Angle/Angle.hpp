#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "constants.h"

class Angle
{
private:
  Point origin;
  int radius;
  float theta;
public:
  Angle(Point origin, int radius);
  Point GetOrigin() const;
  int GetRadius()   const;
  float GetTheta()  const;
  void Update(
    float speed,
    float dt
  );
};