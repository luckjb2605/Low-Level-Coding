#include "Program.hpp"

Program::Program()
: program_running(1)
, window(CreateWindow())
, renderer(SDL_CreateRenderer(window, -1, 0))
, drawer(renderer)
{}

Program::~Program()
{
  // Drawer destroys the renderer.
  SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_Window* Program::CreateWindow()
{
  SDL_Init(SDL_INIT_VIDEO);
  return SDL_CreateWindow(
    "Box collisions approximate PI",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, 0
  );
}

void Program::HandleEvents()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      program_running = false;
    }
  }
}

void Program::Update()
{

}

void Program::Draw()
{
  drawer.ClearBackground();

  drawer.DrawBorders();

  SDL_RenderPresent(renderer);
}

void Program::Run()
{
  while (program_running)
  {
    HandleEvents();
    Update();
    Draw();
    SDL_Delay(delayDurationMs);
  }
}