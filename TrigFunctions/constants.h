#pragma once
#include <stdint.h>

constexpr int WIDTH = 900;
constexpr int HEIGHT = 600;

constexpr int CIRCLE_X = WIDTH/2;
constexpr int CIRCLE_Y = HEIGHT/2;
constexpr int CIRCLE_RADIUS = std::min(WIDTH, HEIGHT)/2 - 10;

constexpr int FPS = 60;
constexpr double FRAME_DURATION = 1000.0/FPS;

constexpr int NUM_OF_POINTS = 100; // For the circumference
constexpr float ANGULAR_SPEED = 30.0f; // Degrees per second

constexpr uint32_t BLACK = 0x000000FF;
constexpr uint32_t WHITE = 0xFFFFFFFF;
constexpr uint32_t PROJX_COLOR = 0xFF0000FF;
constexpr uint32_t PROJY_COLOR = 0x0000FFFF;
constexpr int TRACE_SIZE = 5; // Of dotted link (px)

enum Axis { X, Y };

typedef struct Point
{
  int x;
  int y;
} Point;

typedef struct Line
{
  Point start;
  Point end;
} Line;