#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>

const int WIDTH  = 900;
const int HEIGHT = 600;

const int FPS = 30;
const int frameDurationMs = 1000.0f / FPS;

typedef struct
{
  Uint8 r, g, b, a;
} Color;

typedef struct
{
  float x, y;
} Vector2;

typedef struct
{
  Vector2 center;
  int radius;
  Color color;
} Circle;

const Color WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
const Color BLACK = {0x00, 0x00, 0x00, 0xFF};

void SetDrawColor(SDL_Renderer* renderer, Color color)
{
  SDL_SetRenderDrawColor(renderer,
    color.r, color.g,
    color.b, color.a
  );
}

void ClearScreen(SDL_Renderer* renderer)
{
  SetDrawColor(renderer, BLACK);
  SDL_RenderClear(renderer);
}

void DrawCircle(SDL_Renderer* renderer, const Circle* circle)
{
  SetDrawColor(renderer, circle->color);
  int radius_squared = circle->radius * circle->radius;
  for (int x = circle->center.x - circle->radius; x <= circle->center.x + circle->radius; x++)
  {
    for (int y = circle->center.y - circle->radius; y <= circle->center.y + circle->radius; y++)
    {
      int dx = circle->center.x - x;
      int dy = circle->center.y - y;
      int distance_squared = dx*dx + dy*dy;
      
      if (distance_squared <= radius_squared)
      {
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}

void MoveLightSource(Circle* circle, int x, int y)
{
  circle->center.x = x;
  circle->center.y = y;
}

float GetVector2Mod(Vector2 v)
{
  return sqrt(v.x*v.x + v.y*v.y);
}

float DotProduct(Vector2 v1, Vector2 v2)
{
  return v1.x*v2.x + v1.y*v2.y;
}

/**
 * @return Direction from circle2 pointing to circle1
 */
Vector2 GetDirection(const Circle* circle1, const Circle* circle2)
{
  return (Vector2) {
    circle1->center.x - circle2->center.x,
    circle1->center.y - circle2->center.y
  };
}

Vector2 NormalizeVector(Vector2 v)
{
  float mod = GetVector2Mod(v);
  if (mod == 0) return (Vector2){0, 0};
  return (Vector2) {
    v.x / mod,
    v.y / mod
  };
}

void DrawSubject(SDL_Renderer* renderer, const Circle* lightSource, const Circle* circle)
{
  // Normalize (maybe change this later to magnify with distance to center) each point 
  // Make dot product between point normal and direction normal
  // Make this scalar be the unit for alpha channel.

  int radius_squared = circle->radius * circle->radius;
  Vector2 normalizedDirection = NormalizeVector(GetDirection(circle, lightSource));

  for (int x = circle->center.x - circle->radius; x <= circle->center.x + circle->radius; x++)
  {
    for (int y = circle->center.y - circle->radius; y <= circle->center.y + circle->radius; y++)
    {
      int dx = circle->center.x - x;
      int dy = circle->center.y - y;
      int distance_squared = dx*dx + dy*dy;
      
      if (distance_squared <= radius_squared)
      {
        if (distance_squared > 0.95f * radius_squared)
        {
          Vector2 normalizedVectorPoint = NormalizeVector((Vector2){dx, dy});
          float projectionScalar = DotProduct(normalizedVectorPoint, normalizedDirection);
          Uint8 brightness = fmaxf(0.0f, projectionScalar * 0xFF);
          SetDrawColor(renderer, (Color){
            brightness, brightness,
            brightness, 0xFF
          });
        } else
        {
          SetDrawColor(renderer, BLACK);
        }
        
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}

int main(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "Lightining test from dot product",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event event;

  Circle lightSource = {(Vector2){4.0f/5 * WIDTH, 1.0f/2 * HEIGHT}, 50, WHITE};
  Circle testSubject = {(Vector2){1.0f/2 * WIDTH, 1.0f/2 * HEIGHT}, 50, WHITE};

  int program_running = 1;

  while (program_running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        program_running = 0;
      }

      if (event.motion.state == SDL_PRESSED)
      {
        MoveLightSource(&lightSource, event.button.x, event.button.y);
      }
    }
    ClearScreen(renderer);

    DrawCircle(renderer, &lightSource);
    DrawSubject(renderer, &lightSource, &testSubject);

    SDL_RenderPresent(renderer);
    SDL_Delay(frameDurationMs);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}