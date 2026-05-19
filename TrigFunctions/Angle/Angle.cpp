#include "Angle/Angle.hpp"

Angle::Angle(Point origin, int radius)
  : origin(origin), radius(radius), theta(0)
{}

Point Angle::GetOrigin() const { return origin; }
int Angle::GetRadius()   const { return radius; }
float Angle::GetTheta()  const { return theta; }

void Angle::Update(float speed, float dt)
{
  float speedRadians = speed * M_PI / 180.0f;
  float dtheta = speedRadians * dt;
  theta += dtheta;
  if (theta >= 2*M_PI) theta -= 2*M_PI;
}