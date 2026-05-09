#pragma once
#include <raylib.h>

class Board
{
public:
  const int cellCount;
  const float cellSize;
  const float offset;
  const float windowSize;
  Board(
    int cellCount, 
    float cellSize,
    float offset
  );
  void Draw(Color color1, Color color2);
  void DrawFrame(int thickness, Color color);
  void DrawTitle(int fontSize, Color color);
  void DrawPauseScreen(int fontSize, Color color);
  void DrawScore(int fontSize, Color Color, int score, int thickness);
  Vector2 ToGrid(Vector2 pos);
  Vector2 GetRandomCell();
};