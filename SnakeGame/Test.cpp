#include <raylib.h>

bool hitBorder(int pos, int ballRadius, int windowSize)
{
  return (
    pos + ballRadius >= windowSize ||
    pos - ballRadius <= 0
  );
}

int main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  
  int xPos = 100;
  int yPos = 100;

  int xSpeed = 5;
  int ySpeed = 5;

  const int BALL_RADIUS = 15;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
  SetTargetFPS(60);

  while(!WindowShouldClose())
  {
    xPos += xSpeed;
    yPos += ySpeed;

    if (hitBorder(xPos, BALL_RADIUS, SCREEN_WIDTH))
      xSpeed *= -1;

    if (hitBorder(yPos, BALL_RADIUS, SCREEN_HEIGHT))
      ySpeed *= -1;

    BeginDrawing();
      ClearBackground(BLACK);
      DrawCircle(xPos, yPos, BALL_RADIUS, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}