#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "constants.h"
#include "drawer.h"

int main(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "TrigFunctions Visualizer",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  Circle trigCircle = {LEFT_MARGIN, HEIGHT/2, LEFT_MARGIN - 10};
  
  int program_running = 1;
  SDL_Event event;
  while (program_running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type==SDL_QUIT)
        program_running = 0;
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    DrawX_Axis(renderer);
    DrawY_Axis(renderer);

    DrawTrigCircle(renderer, trigCircle);

    SDL_RenderPresent(renderer);
    SDL_Delay(FRAME_DURATION);
  }
  return 0;
}