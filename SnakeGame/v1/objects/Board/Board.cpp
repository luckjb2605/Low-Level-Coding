#include "Board.h"

Board::Board(int cellCount, float cellSize)
  : cellCount(cellCount), cellSize(cellSize) {}

void Board::Draw(Color color1, Color color2) const
{
  ClearBackground(color1);

  for (int col = 0; col <= cellCount; col++)
  {
    for (int row = 0; row <= cellCount; row++)
    {
      if ((col + row) % 2 == 0)
      {
        DrawRectangle(
          row * cellSize,
          col * cellSize,
          cellSize,
          cellSize,
          color2
        );
      }
    }
  }
}

Vector2 Board::Pos(int x, int y)
{
  return (Vector2) {
    x * cellSize,
    y * cellSize
  };
}

int Board::CellSize()
{
  return cellSize;
}

int Board::Size()
{
  return cellCount;
}