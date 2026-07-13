#include "Drawer.hpp"

Drawer::Drawer(SDL_Renderer* renderer)
  : renderer(renderer)
{
  SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
  xBorder = screenHeight * 9 / 10;
  yBorder = screenWidth  * 1 / 15;
}

Drawer::~Drawer()
{
  SDL_DestroyRenderer(renderer);
}

void Drawer::SetDrawColor(Color color)
{
  SDL_SetRenderDrawColor(renderer,
    color.r, color.g,
    color.b, color.a
  );
}

void Drawer::ClearBackground()
{
  SetDrawColor(BLACK);
  SDL_RenderClear(renderer);
}

void Drawer::DrawBorders()
{
  SetDrawColor(WHITE);
  SDL_RenderDrawLine(renderer,
    0, xBorder,
    screenWidth, xBorder
  );
  SDL_RenderDrawLine(renderer,
    yBorder, 0,
    yBorder, screenHeight
  );
}