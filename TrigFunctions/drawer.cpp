#include "drawer.h"

void DrawX_Axis(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderDrawLine(
    renderer,
    LEFT_MARGIN,
    0,
    LEFT_MARGIN,
    HEIGHT
  );
}

void DrawY_Axis(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderDrawLine(
    renderer,
    0,
    HEIGHT/2,
    WIDTH,
    HEIGHT/2
  );
}

// Talvez a velocidade compensava a memoria.
void ComputeCircle(Point(*points)[NUM_OF_POINTS], Circle circle)
{
  for (int i=0;i<NUM_OF_POINTS;i++)
  {
    double theta = i*360.0/NUM_OF_POINTS;
    int x = circle.x + circle.radius * cos(theta);
    int y = circle.y + circle.radius * sin(theta);
    points[0][i] = {x,y};
  }
}

void DrawTrigCircle(SDL_Renderer* renderer, Point(&points)[NUM_OF_POINTS])
{
  for (auto point : points)
  {
    SDL_RenderDrawPoint(renderer,point.x,point.y);
  }
}

void UpdateClockHand(ClockHand* hand, Point(&points)[NUM_OF_POINTS])
{
  hand->theta += M_PI*2.0 / STEPS;
  if (hand->theta >= M_PI*2)
    hand->theta = 0;
  hand->pointerX = circle.x + circle.radius*cos(hand->theta);
  hand->pointerY = circle.y - circle.radius*sin(hand->theta);
  printf("theta: %.4f, x: %.4f, y: %.4f\n",
    hand->theta, circle.radius*cos(hand->theta), circle.radius*sin(hand->theta));
}

void DrawClockHand(SDL_Renderer* renderer, Circle circle, ClockHand* hand)
{
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderDrawLine(
    renderer,
    circle.x,
    circle.y,
    hand->pointerX,
    hand->pointerY
  );
}