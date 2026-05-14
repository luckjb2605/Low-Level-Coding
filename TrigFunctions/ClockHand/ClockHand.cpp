#include "ClockHand/ClockHand.h"

ClockHand::ClockHand()
  : angle(0) {}
Point ClockHand::GetTail()  const { return tail; }
Point ClockHand::GetHead()  const { return head; }
float ClockHand::GetAngle() const { return angle; };

void ClockHand::Update(Circle circle, float dt)
{
  angle += ANGULAR_SPEED * dt;
  if (angle >= 360) angle -= 360;
  
  tail = circle.GetCenter();

  int currentPoint = NUM_OF_POINTS * (angle / 360.0f);
  head.x = circle.GetPoint(currentPoint).x;
  head.y = circle.GetPoint(currentPoint).y;
}
