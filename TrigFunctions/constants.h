#pragma once

constexpr int WIDTH = 900;
constexpr int HEIGHT = 600;

constexpr int FPS = 60;
constexpr double FRAME_DURATION = 1000.0/FPS;

constexpr int LEFT_MARGIN = 150;
constexpr int STEPS = 500;

constexpr int BLACK = 0x00000000;
constexpr int WHITE = 0x00ffffff;

typedef struct Circle
{
  int x;
  int y;
  int radius;
} Circle;