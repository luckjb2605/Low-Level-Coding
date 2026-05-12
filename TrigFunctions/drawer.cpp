#define _USE_MATH_DEFINES
#include <cmath>
#include "drawer.h"
#include "constants.h"

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

void DrawTrigCircle(SDL_Renderer* renderer, Circle circle)
{
  for (double theta = 0; theta < M_PI*2; theta+=M_PI*2/STEPS)
  {
    int x = circle.x + circle.radius * cos(theta);
    int y = circle.y + circle.radius * sin(theta);
    SDL_RenderDrawPoint(renderer,x,y);
  }
}
