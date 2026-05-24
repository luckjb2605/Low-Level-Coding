#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// window dimensions
const int WIDTH = 900;
const int HEIGHT = 600;

// colors (rgba)
const Uint32 WHITE = 0xFFFFFFFF;
const Uint32 BLACK = 0x000000FF;

// circle
const int CIRCLE_RADIUS = 100;

// simulation
const float g = 1000.0f;
const int FPS = 60;
const Uint32 FRAME_DURATION = 1000/FPS;

typedef struct Clock
{
  Uint64 current, last;
} Clock;

typedef struct Circle
{
  float x, y;
  int radius;
  float speed;
} Circle;

void SetDrawColor(SDL_Renderer* renderer, Uint32 color)
{
  SDL_SetRenderDrawColor(renderer,
    /*r*/ (color >> (32-8*1)) & 0xFF,
    /*g*/ (color >> (32-8*2)) & 0xFF,
    /*b*/ (color >> (32-8*3)) & 0xFF,
    /*a*/ (color >> (32-8*4)) & 0xFF
  );
}

void DrawCircle(SDL_Renderer* renderer, Circle circle)
{
  int radius_squared = circle.radius * circle.radius;
  int centerX = (int)circle.x;
  int centerY = (int)circle.y;
  for (
    int x = centerX - circle.radius; 
    x <= centerX + circle.radius;
    x++
  ) {
    for (
      int y = centerY - circle.radius;
      y <= centerY + circle.radius;
      y++
    ) {
      int dx = centerX - x;
      int dy = centerY - y;
      int distance_squared = dx*dx + dy*dy;
      if (distance_squared <= radius_squared)
        SDL_RenderDrawPoint(renderer,x, y);
    }
  }
}

float GetDeltaTime(Clock* clock)
{
  clock->current = SDL_GetPerformanceCounter();
  float dt = (float)(clock->current - clock->last)
    / SDL_GetPerformanceFrequency();
  clock->last = clock->current;
  return (dt > 0.05) ? 0.05 : dt;
}

void Fall(Circle* circle, float acceleration, float dt)
{
  circle->speed += acceleration * dt;
  circle->y += circle->speed * dt;
}

void Reset(Circle* circle)
{
  circle->x = -CIRCLE_RADIUS;
  circle->y = -CIRCLE_RADIUS;
  circle->radius = CIRCLE_RADIUS;
  circle->speed = 0;
}

void Delay(Uint64 frameStart, Uint32 FRAME_DURATION)
{
  float frameTimeMs = (float)(SDL_GetPerformanceCounter() - frameStart)
    / SDL_GetPerformanceFrequency() * 1000.0f;
  if (frameTimeMs < FRAME_DURATION)
    SDL_Delay(FRAME_DURATION - frameTimeMs);
}

int main()
{
  // SETUP
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "Gravity",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  
  // OBJECTS
  Clock clock = {
    SDL_GetPerformanceCounter(),
    SDL_GetPerformanceCounter()
  };
  Circle circle;
  Reset(&circle);

  // PROGRAM
  int running = 1;
  SDL_Event event;
  while (running)
  {
    // SCREEN FLUSH
    SetDrawColor(renderer, BLACK);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = 0;
      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        circle.x = event.button.x;
        circle.y = event.button.y;
      }
    }

    float dt = GetDeltaTime(&clock);
    
    SetDrawColor(renderer, WHITE);
    DrawCircle(renderer, circle);
    Fall(&circle, g, dt);
    if ((circle.y - circle.radius) >= HEIGHT)
    {
      Reset(&circle);
      // circle.y = -circle.radius;
    }

    // SCREEN UPDATE AND DELAY
    SDL_RenderPresent(renderer);
    Delay(clock.current, FRAME_DURATION);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}