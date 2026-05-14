#include "Circle/Circle.h"

Circle::Circle(Point center, int radius)
  : center(center)
  , radius(radius)
{}

int   Circle::GetRadius() const { return radius; }
Point Circle::GetCenter() const { return center; }
Point Circle::GetPoint(int index) const
{
  return points[index];
}

void Circle::ComputePoints()
{
  for (int i=0;i<NUM_OF_POINTS;i++)
  {
    double theta = i*M_PI*2.0/NUM_OF_POINTS;
    int x = center.x + radius * cos(theta);
    int y = center.y - radius * sin(theta);
    points[i] = {x,y};
  }
}