#pragma once
#include <stdint.h>

constexpr int WIDTH = 900;
constexpr int HEIGHT = 600;
constexpr int MARGIN = 10;

constexpr int CIRCLE_RADIUS = 100;
constexpr int CIRCLE_X = CIRCLE_RADIUS + MARGIN;
constexpr int CIRCLE_Y = HEIGHT / 2;
// constexpr int CIRCLE_Y = CIRCLE_RADIUS + MARGIN;
// constexpr int CIRCLE_RADIUS = std::min(WIDTH, HEIGHT)/2 - 10;

constexpr int FPS = 60;
constexpr double FRAME_DURATION = 1000.0/FPS;

constexpr int NUM_OF_POINTS = 1200; // For the circumference
constexpr float ANGULAR_SPEED = 30.0f; // Degrees per second
constexpr float STEP_ANGLE = 360.0f / NUM_OF_POINTS;

constexpr uint32_t BLACK = 0x000000FF;
constexpr uint32_t WHITE = 0xFFFFFFFF;
constexpr uint32_t GREEN = 0x00FF00FF;
constexpr uint32_t RED = 0xFF0000FF;
constexpr uint32_t BLUE = 0x0000FFFF;
constexpr int TRACE_SIZE = 5; // Of dotted link (px)

constexpr int FUNCTION_POINTS = WIDTH - CIRCLE_X;
constexpr bool HORIZONTIFY_COSINE = true;
constexpr int ANGLE_RADIUS = 10;


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