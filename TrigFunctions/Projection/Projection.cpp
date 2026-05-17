#include "Projection/Projection.h"

Projection::Projection(Axis axis, Circle* circle, uint32_t color)
  : circle(circle)
  , center(circle->GetCenter())
  , axis(axis)
  , color(color)
{}
Point Projection::GetCenter()   const { return center; }
Point Projection::GetHead()     const { return head; }
uint32_t Projection::GetColor() const { return color; }

float RoundDown(float numToRound, float rounder)
{
  if (rounder==0) return 0;
  return std::floor(numToRound/rounder) * rounder;
}

void Projection::Update(float angle)
{
  angle = RoundDown(angle, STEP_ANGLE);
  if (axis == X)
  {
    head.x = center.x +
      circle->GetRadius() * cos(angle*M_PI/180);
    head.y = center.y;
  } else
  if (axis == Y)
  {
    head.x = center.x;
    head.y = center.y -
      circle->GetRadius() * sin(angle*M_PI/180);
  }
}

/**
 * Returns an array of points that
 * link this projections's head to
 * the provided point.
 */
std::vector<Line> Projection::GetLink(Point point)
{
  int dx = point.x - head.x;
  int dy = point.y - head.y;
  float distance = sqrt(dx*dx+dy*dy);
  
  int steps;
  if (TRACE_SIZE == 0) steps = 1;
  else steps = distance / TRACE_SIZE;
  
  std::vector<Line> link;
  link.reserve(steps);
  
  for (int i=0; i<(steps-1); i+=2)
  {
    float t1 = (float)(i)   / steps;
    float t2 = (float)(i+1) / steps;
    int x1 = head.x + dx * t1;
    int y1 = head.y + dy * t1;
    int x2 = head.x + dx * t2;
    int y2 = head.y + dy * t2;
    link.push_back({{x1,y1}, {x2,y2}});
  }

  return link;
}