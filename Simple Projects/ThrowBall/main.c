#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define FPS 60

#define WHITE 0x00ffffff
#define BLACK 0x00000000

typedef struct Vector
{
  double x;
  double y;
} Vector;

/**
 * int x;
 * int y;
 * int radius;
 * double speed;
 */
typedef struct Circle
{
  Vector pos;
  int radius;
  Vector speed;
  int radius_squared;
} Circle;

int PosInsideCircle(Circle* circle, Vector pos)
{
  int dx = circle->pos.x - pos.x;
  int dy = circle->pos.y - pos.y;
  int distance_squared = dx*dx + dy*dy;
  return distance_squared < circle->radius_squared;
}

/**
 * Paints the given circle on the screen with the given color.
 * Compares the squares of the distance to the center and the radius
 * of the circle.
 */
void FillCircle(SDL_Surface* surface, Circle* circle, Uint32 color)
{
  circle->radius_squared = circle->radius * circle->radius;
  for (
    int x = circle->pos.x - circle->radius;
    x <= circle->pos.x + circle->radius;
    x++
  ) {
    for (
      int y = circle->pos.y - circle->radius;
      y <= circle->pos.y + circle->radius;
      y++
    ) {
      if (PosInsideCircle(circle, (Vector){x,y}))
      {
        SDL_Rect pixel = {x, y, 1, 1};
        SDL_FillRect(surface, &pixel, color);
      }
    }
  }
}

void DragCircle(Circle* circle, Vector pos)
{
  circle->pos.x = pos.x;
  circle->pos.y = pos.y;
}

typedef struct Cursor
{
  Vector pos;
  Vector speed;
  Uint32 last_record;
} Cursor;

/**
 * Returns the speed of the cursor based on the tracking of its position.
 * The unit is pixels per millisecond (px/ms).
 */
void UpdateCursor(Cursor* cursor, SDL_MouseMotionEvent* event)
{
  Uint32 dt = event->timestamp - cursor->last_record;
  if (dt==0) return;
  double xSpeed = (event->x - cursor->pos.x) / (double)dt;
  double ySpeed = (event->y - cursor->pos.y) / (double)dt;
  cursor->speed = (Vector){xSpeed, ySpeed};
  cursor->pos = (Vector){event->x,event->y};
  cursor->last_record = event->timestamp;
}

void MoveCircle(Circle* circle, double frame_duration)
{
  circle->pos.x += circle->speed.x * frame_duration;
  circle->pos.y += circle->speed.y * frame_duration;
}

int main(void)
{
  // ============= SETUP ==============

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "Drag and Throw Ball",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0
  );
  SDL_Surface* surface = SDL_GetWindowSurface(window);

  // ============ OBJECTS =============

  SDL_Rect eraser = {0,0,WIDTH,HEIGHT};
  Circle circle = {{WIDTH/2, HEIGHT/2}, 100, 0};
  Cursor cursor = {{0,0},{0,0},0};

  // =========== SIMULATION ===========

  int simulation_running = 1;
  int grabbed = 0;
  double frame_duration = 1.0/FPS*1000.0; // ms
  SDL_Event event;
  while (simulation_running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type==SDL_QUIT)
        simulation_running = 0;
      if (event.type==SDL_MOUSEBUTTONDOWN)
      {
        if (PosInsideCircle(&circle,
          (Vector){event.motion.x,event.motion.y}
        )) {
          grabbed = 1;
        }
      }
      if (event.type==SDL_MOUSEBUTTONUP &&
        grabbed
      ) {
        circle.speed = cursor.speed;
        grabbed = 0;
      }
      if (
        event.type==SDL_MOUSEMOTION &&
        grabbed
      ) {
        DragCircle(
          &circle,
          (Vector){
            event.motion.x,
            event.motion.y
          }
        );
        UpdateCursor(&cursor, &event.motion);
      }
    }
    SDL_FillRect(surface, &eraser, BLACK);

    if (!grabbed)
      MoveCircle(&circle, frame_duration);

    FillCircle(surface, &circle, WHITE);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(frame_duration);
  }
  return 0;
}