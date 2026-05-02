#include "Board.h"

Board::Board(int cellCount, float cellSize)
  : cellCount(cellCount), cellSize(cellSize) {}

void Board::Draw(Color color1, Color color2)
{
  ClearBackground(color1);
  for (int i = 0; i <= cellCount; i++)
  {
    for (int j = 0; j <= cellCount; j++)
    {
      if ((i + j) % 2 == 0)
      {
        Vector2 pos = ToGrid({(float)i, (float)j});
        DrawRectangle(
          pos.x,
          pos.y,
          cellSize,
          cellSize,
          color2
        );
      }
    }
  }
}

Vector2 Board::GetRandomCell()
{
  return ToGrid({
    (float)GetRandomValue(0, cellCount - 1),
    (float)GetRandomValue(0, cellCount - 1)
  });
}

Vector2 Board::ToGrid(Vector2 pos)
{
  return {
    pos.x * cellSize,
    pos.y * cellSize
  };
}