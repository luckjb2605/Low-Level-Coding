#pragma once
#include <raylib.h>

class Board
{
  public:
    const int cellCount;
    const float cellSize;
    Board(int cellCount, float cellSize);
    void Draw(Color color1, Color color2);
    Vector2 ToGrid(Vector2 pos);
    Vector2 GetRandomCell();
};