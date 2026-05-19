#include "ClockHand/ClockHand.h"

ClockHand::ClockHand(Point tail)
  : tail(tail)
{}
Point ClockHand::GetTail()  const { return tail; }
Point ClockHand::GetHead()  const { return head; }

void ClockHand::Update(Circle& circle, float angle)
{
  int currentPoint = NUM_OF_POINTS * (angle / (2*M_PI));
  head.x = circle.GetPoint(currentPoint).x;
  head.y = circle.GetPoint(currentPoint).y;
}
