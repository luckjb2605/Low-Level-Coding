#include "Drawer/Drawer.h"

Drawer::Drawer(SDL_Renderer* renderer)
  : renderer(renderer)
{}

void Drawer::SetDrawColor(uint32_t color)
{
  SDL_SetRenderDrawColor(renderer, 
    (color >> (32-1*8) & 0xFF),
    (color >> (32-2*8) & 0xFF),
    (color >> (32-3*8) & 0xFF),
    (color >> (32-4*8) & 0xFF)
  );
}

void Drawer::ClearScreen()
{
  SetDrawColor(BLACK);
  SDL_RenderClear(renderer);
}

void Drawer::DrawX_Axis()
{
  SetDrawColor(WHITE);
  SDL_RenderDrawLine(renderer,
    0, CIRCLE_Y,
    WIDTH, CIRCLE_Y
  );
}

void Drawer::DrawY_Axis()
{
  SetDrawColor(WHITE);
  SDL_RenderDrawLine(renderer,
    CIRCLE_X, 0,
    CIRCLE_X, HEIGHT
  );
}

void Drawer::DrawTrigCircle(const Circle* circle)
{
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  for (int i=0; i<NUM_OF_POINTS; i++)
  {
    SDL_RenderDrawPoint(
      renderer,
      circle->GetPoint(i).x,
      circle->GetPoint(i).y
    );
  }
}

void Drawer::DrawClockHand(const ClockHand* clockHand)
{
  SetDrawColor(WHITE);
  SDL_RenderDrawLine(
    renderer,
    clockHand->GetTail().x,
    clockHand->GetTail().y,
    clockHand->GetHead().x,
    clockHand->GetHead().y
  );
}

void Drawer::DrawProjection(const Projection* p)
{
  SetDrawColor(p->GetColor());
  SDL_RenderDrawLine(renderer,
    p->GetCenter().x,
    p->GetCenter().y,
    p->GetHead().x,
    p->GetHead().y
  );
}

void Drawer::DrawLink(const std::vector<Line> &lines, uint32_t color)
{
  SetDrawColor(color);
  for (auto line : lines)
    SDL_RenderDrawLine(renderer,
      line.start.x,
      line.start.y,
      line.end.x,
      line.end.y
    );
}

void Drawer::DrawFunction(const Function& function, uint32_t color)
{
  SetDrawColor(color);

  const auto& points = function.GetPoints();

  if (function.GetFunctionType() == Horizontal)
  {
    for (int x=0; x<points.size(); x++)
    {
      SDL_RenderDrawPoint(renderer,
        x + function.GetOrigin(), 
        points.at(x)
      );
    }
  } else
  if (function.GetFunctionType() == Vertical)
  {
    for (int y=0; y<points.size(); y++)
    {
      SDL_RenderDrawPoint(renderer,
        points.at(y),
        y + function.GetOrigin()
      );
    }
  }
}