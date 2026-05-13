#pragma once

constexpr int WIDTH = 900;
constexpr int HEIGHT = 600;

constexpr int FPS = 60;
constexpr double FRAME_DURATION = 1000.0/FPS;

constexpr int LEFT_MARGIN = 150;
constexpr int NUM_OF_POINTS = 500;

constexpr int BLACK = 0x00000000;
constexpr int WHITE = 0x00ffffff;

constexpr int STEPS = 300;
constexpr int ANGULAR_SPEED = 10;

typedef struct Point
{
  int x;
  int y;
} Point;

typedef struct Circle
{
  int x;
  int y;
  int radius;
} Circle;

typedef struct ClockHand
{
  double theta;
  int pointerX;
  int pointerY;
} ClockHand;