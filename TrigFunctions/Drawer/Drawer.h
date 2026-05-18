#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <SDL2/SDL.h>

#include "Projection/Projection.h"
#include "ClockHand/ClockHand.h"
#include "Function/Function.hpp"
#include "Circle/Circle.h"
#include "constants.h"

class Drawer
{
private:
  SDL_Renderer* renderer;
  void SetDrawColor(uint32_t);
public:
  Drawer(SDL_Renderer*);
  void ClearScreen();
  void DrawX_Axis();
  void DrawY_Axis();
  void DrawTrigCircle(const Circle*);
  void DrawClockHand(const ClockHand*);
  void DrawProjection(const Projection*);
  void DrawLink(const std::vector<Line>&, uint32_t color);
  void DrawFunction(const Function&, uint32_t color);
};
