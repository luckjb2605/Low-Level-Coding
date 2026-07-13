#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Drawer.hpp"

class Program
{
private:
  static constexpr int SCREEN_WIDTH  = 900;
  static constexpr int SCREEN_HEIGHT = 600;
  
  static constexpr int frameRate = 60;
  static constexpr int delayDurationMs = 1000.0f / frameRate;

  bool program_running;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;

  Drawer drawer;

  static SDL_Window* CreateWindow();
  
  void HandleEvents();
  void Update();
  void Draw();
public:
  Program();
  ~Program();
  void Run();
};