#define SDL_MAIN_HANDLED
#define _USE_MATH_DEFINES
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

// Apparently 0x00RRGGBB
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_YELLOW 0x00ffdd77

#define RAYS_NUMBER 200
#define SPEED 400/60

typedef enum Direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direction;

typedef struct Pos
{
  double x;
  double y;
} Pos;

typedef struct Circle
{
  double x;
  double y;
  double radius;
  int speed;
  Direction dir;
} Circle;

typedef struct Ray
{
  double x_start, y_start;
  double angle;
  double x_end, y_end;
} Ray;

typedef struct Bounds
{
  float left;
  float right;
  float top;
  float bottom;
} Bounds;

void FillCircle(SDL_Surface* surface, Circle circle, Uint32 color)
{
  double radius_squared = pow(circle.radius,2);
  for(
    double x = circle.x - circle.radius;
    x <=circle.x + circle.radius;
    x++
  ) {
    for(
      double y = circle.y - circle.radius;
      y <=circle.y + circle.radius;
      y++
    ) {
      double distance_squared = pow(x-circle.x,2) + pow(y-circle.y,2);
      if (distance_squared < radius_squared)
      {
        SDL_Rect pixel = (SDL_Rect){x,y,1,1};
        SDL_FillRect(surface, &pixel, color);
      }
    }
  }
}

void generate_rays(Circle circle, Ray rays[RAYS_NUMBER])
{
  for (int i=0; i<RAYS_NUMBER; i++)
  {
    double angle = ((double)i/RAYS_NUMBER)*2*M_PI; // a = tan(angle)
    struct Ray ray = {
      circle.x + circle.radius*cos(angle),
      circle.y + circle.radius*sin(angle),
      angle
    };
    rays[i] = ray;
  }
}

void FillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], Circle shadow, Uint32 color)
{
  double radius_squared = pow(shadow.radius, 2);
  for (int i=0; i<RAYS_NUMBER; i++)
  {
    Ray ray = rays[i];
    
    int end_of_screen = 0;
    int object_hit = 0;
    
    double x_draw = ray.x_start;
    double y_draw = ray.y_start;
    while (!(end_of_screen || object_hit))
    {
      if (x_draw < 0 || x_draw > WIDTH)
        end_of_screen = 1;
      if (y_draw < 0 || y_draw > WIDTH)
        end_of_screen = 1;
      
      SDL_Rect pixel = (SDL_Rect){x_draw,y_draw,1,1};
      SDL_FillRect(surface, &pixel, color);

      double distance_squared = 
        pow(x_draw-shadow.x,2) + pow(y_draw-shadow.y,2);
      if (distance_squared < radius_squared)
        object_hit = 1;

      x_draw += cos(ray.angle);
      y_draw += sin(ray.angle);
      
    }
  }
}

void move_shadow_circle(
  Circle* circle, 
  double margin,
  Bounds bounds
) {
  switch(circle->dir)
  {
    case RIGHT:
      circle->x += circle->speed;
      if (circle->x >= bounds.right)
      {
        circle->x = bounds.right;
        circle->dir = DOWN;
      } break;
    case DOWN:
      circle->y += circle->speed;
      if (circle->y >= bounds.bottom)
      {
        circle->y = bounds.bottom;
        circle->dir = LEFT;
      } break;
    case LEFT:
      circle->x -= circle->speed;
      if (circle->x <= bounds.left)
      {
        circle->x = bounds.left;
        circle->dir = UP;
      } break;
    case UP:
      circle->y -= circle->speed;
      if (circle->y <= bounds.top)
      {
        circle->x = bounds.top;
        circle->dir = RIGHT;
      }
  }
}

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "Raytracing", 
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH,
    HEIGHT,
    0
  );
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  
  double shadow_size = 0.20 * fmin(WIDTH,HEIGHT);
  double margin = 0.04 * fmin(WIDTH,HEIGHT);
  double circle_size = 0.15 * fmin(WIDTH,HEIGHT);

  Bounds bounds = {
    margin + shadow_size,
    WIDTH - (margin + shadow_size),
    margin + shadow_size,
    HEIGHT - (margin + shadow_size)
  };
  
  Circle circle = {circle_size, circle_size, circle_size};
  Circle shadow_circle = {
    shadow_size + margin,
    shadow_size + margin,
    shadow_size, SPEED, RIGHT};
  SDL_Rect erase_rect = {0,0,WIDTH,HEIGHT};
  
  Ray rays[RAYS_NUMBER];
  
  int simulation_running = 1;
  SDL_Event event;
  while ( simulation_running )
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        simulation_running = 0;
      }
      if (event.motion.state != 0
        //  && event.type == SDL_MOUSEMOTION
      ) {
        circle.x = event.motion.x;
        circle.y = event.motion.y;
        generate_rays(circle, rays);
      }
    }
    SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
    FillCircle(surface, shadow_circle, COLOR_WHITE);

    FillCircle(surface, circle, COLOR_WHITE);
    FillRays(surface, rays, shadow_circle, COLOR_YELLOW);
    
    move_shadow_circle(&shadow_circle, margin, bounds);
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(16);
  }
  return 0;
}