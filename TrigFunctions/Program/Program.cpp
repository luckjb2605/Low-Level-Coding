#include "Program/Program.h"

Program::Program()
  : window(CreateWindow())
  , renderer(SDL_CreateRenderer(window, -1, 0))
  , drawer(renderer)
  , trigCircle({CIRCLE_X, CIRCLE_Y}, CIRCLE_RADIUS)
  , projX({X, &trigCircle, PROJX_COLOR})
  , projY({Y, &trigCircle, PROJY_COLOR})
  , running(true)
{}

SDL_Window* Program::CreateWindow()
{
  SDL_Init(SDL_INIT_VIDEO);
  return SDL_CreateWindow(
    "TrigFunctions Visualizer",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0
  );
}

void Program::HandleEvents()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type==SDL_QUIT)
      running = false;
  }
}

void Program::Update()
{
  dt = timer.Update();
  clockHand.Update(trigCircle, dt);
  projX.Update(clockHand.GetAngle());
  projY.Update(clockHand.GetAngle());
}

void Program::Draw()
{
  drawer.ClearScreen();

  drawer.DrawX_Axis();
  drawer.DrawY_Axis();

  drawer.DrawProjection(&projX);
  drawer.DrawProjection(&projY);

  drawer.DrawLink(
    projX.GetLink(clockHand.GetHead()),
    projX.GetColor());
  drawer.DrawLink(
    projY.GetLink(clockHand.GetHead()),
    projY.GetColor());

  drawer.DrawTrigCircle(&trigCircle);
  drawer.DrawClockHand(&clockHand);

  SDL_RenderPresent(renderer);
}

void Program::Run()
{
  trigCircle.ComputePoints();
  while (running)
  {
    HandleEvents();
    Update();
    Draw();
    SDL_Delay(FRAME_DURATION);
    printf(
      "Angle: %.4f, Cos: %.4f, Sin: %.4f\n",
      clockHand.GetAngle(),
      cos(clockHand.GetAngle()),
      sin(clockHand.GetAngle())
    );
  }
}

Program::~Program()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}