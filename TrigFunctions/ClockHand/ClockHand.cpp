#include "ClockHand/ClockHand.h"

ClockHand::ClockHand()
  : angle(0) {}
Point ClockHand::GetTail()  const { return tail; }
Point ClockHand::GetHead()  const { return head; }
float ClockHand::GetAngle() const { return angle; };

void ClockHand::Update(Circle circle, float dt)
{
  float dtheta = ANGULAR_SPEED * dt;
  angle += dtheta;
  if (angle >= 360) angle -= 360;
  
  // Don't need to do this every frame (Own circle?)
  tail = circle.GetCenter();

  int currentPoint = NUM_OF_POINTS * (angle / 360.0f);
  head.x = circle.GetPoint(currentPoint).x;
  head.y = circle.GetPoint(currentPoint).y;
}
