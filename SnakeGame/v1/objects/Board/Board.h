#pragma once

#include <raylib.h>

class Board
{
  public:
    Board(int cellCount, float cellSize);
    
    void Draw(Color color1, Color color2) const;
    Vector2 Pos(int x, int y);

    int CellSize();
    int Size();
  private:
    const int cellCount;
    const float cellSize;
};