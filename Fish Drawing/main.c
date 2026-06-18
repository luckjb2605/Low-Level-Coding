#define SDL_MAIN_HANDLED
#define _USE_MATH_DEFINES
#include <SDL2/SDL.h>
#include <math.h>

const int WIDTH = 900;
const int HEIGHT = 600;
const int FPS = 60;
const float FRAME_DURATION
  = 1000.0f / FPS;
const int LIMIT = 1000;

const int x_offset = 445;
const int y_offset = 300;
const int size = 300;

typedef struct
{
  int x, y;
} Point;

Point GetStart(int k)
{
  float x, y;

  x = x_offset + size * (sin(4*M_PI*k/1000) - cos(4*M_PI*k/1000));
  y = y_offset + size * (1.0f/2 * pow(cos(6*M_PI*k/1000 + 2*M_PI/5), 3));

  return (Point){x, HEIGHT - y + 1};
}

Point GetEnd(int k)
{
  float x, y;

  x = x_offset + size * (-2.0f/15 * sin(6*M_PI*k/1000 + M_PI/10));
  y = y_offset + size * (4.0f/5 * sin(2*M_PI*k/1000 + M_PI/10));

  return (Point){x, HEIGHT - y + 1};
}

void DrawLine(SDL_Renderer* renderer, int k)
{
  Point start = GetStart(k);
  Point end = GetEnd(k);

  printf(" (%d, %d)", start.x, start.y);
  printf(" (%d, %d)\n", end.x, end.y);
  
  SDL_RenderDrawLine(renderer,
    start.x, start.y,
    end.x, end.y
  );
}

int main(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "Hamid Naderi Yeganeh Fish",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0
  );
  SDL_Renderer* renderer = 
    SDL_CreateRenderer(window, -1, 0);
  SDL_Event event;

  SDL_SetRenderDrawColor(renderer,255,255,255,255);

  int program_running = 1;
  int drawing_finished = 0;
  
  int k = 1;

  while (program_running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        program_running = 0;
      }
    }

    if (!drawing_finished)
    {
      DrawLine(renderer, k);
      printf("%d", k);
      
      k++;
      
      if (k > LIMIT)
      {
        drawing_finished = 1;
      }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(FRAME_DURATION);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}