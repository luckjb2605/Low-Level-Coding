#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "constants.h"
#include "Drawer/drawer.h"
#include "Circle/Circle.h"
#include "DeltaTimer/DeltaTimer.h"
#include "ClockHand/ClockHand.h"

class Program
{
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;

  DeltaTimer timer;
  Drawer drawer;
  Circle trigCircle;
  ClockHand clockHand;
  Projection projX;
  Projection projY;

  bool running;
  float dt;
  
  void HandleEvents();
  void Update();
  void Draw();
  
  static SDL_Window* CreateWindow();
public:
  Program();
  ~Program();
  void Run();
};