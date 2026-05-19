#include "Program/Program.h"

Program::Program()
  : window(CreateWindow())
  , renderer(SDL_CreateRenderer(window, -1, 0))
  , drawer(renderer)
  , trigCircle({CIRCLE_X, CIRCLE_Y}, CIRCLE_RADIUS)
  , angle(trigCircle.GetCenter(), ANGLE_RADIUS)
  , clockHand(trigCircle.GetCenter())
  , projX({X, &trigCircle, RED})
  , projY({Y, &trigCircle, BLUE})
  , sineFunction(Horizontal, CIRCLE_X)
  , cosineFunction(HORIZONTIFY_COSINE ? Horizontal : Vertical, CIRCLE_X)
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

int HorizontifyFunction(int x)
{
  int cosineValue = CIRCLE_X - x;
  // You have to sum cosineValue, because coming from x values,
  // "up" (right) increases, but in y values, it decreases.
  int yRepresentation = CIRCLE_Y + cosineValue;
  return yRepresentation;
}

void Program::Update()
{
  dt = timer.Update();
  angle.Update(ANGULAR_SPEED, dt);
  clockHand.Update(
    trigCircle,
    angle.GetTheta()
  );
  projX.Update(angle.GetTheta());
  projY.Update(angle.GetTheta());
  sineFunction.Update(projY.GetHead().y);
  if (HORIZONTIFY_COSINE)
    cosineFunction.Update(HorizontifyFunction(projX.GetHead().x));
  else
    cosineFunction.Update(projX.GetHead().x);
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

  drawer.DrawFunction(
    cosineFunction,
    RED);
  drawer.DrawFunction(
    sineFunction,
    BLUE);

  drawer.DrawAngle(angle);

  SDL_RenderPresent(renderer);
}

void Program::PrintState()
{
  printf(
    "Angle: %.2f, Sine: %.2f, Cosine: %.2f\n",
    angle.GetTheta(),
    projY.GetModulus(),
    projX.GetModulus()
  );
}

void Program::Run()
{
  trigCircle.ComputePoints();
  while (running)
  {
    HandleEvents();
    Update();
    Draw();
    PrintState();
    SDL_Delay(FRAME_DURATION);
  }
}

Program::~Program()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}