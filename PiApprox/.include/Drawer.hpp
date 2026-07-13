#pragma once
#include <SDL2/SDL.h>
#include "Color.hpp"

class Drawer
{
private:
  SDL_Renderer* renderer;

  int screenWidth, screenHeight;
  int xBorder, yBorder;

  void SetDrawColor(Color);
public:
  Drawer(SDL_Renderer*);
  ~Drawer();
  
  void ClearBackground();
  void DrawBorders();
};