#include "Board.h"

Board::Board(
  int cellCount, 
  float cellSize,
  float offset
) : cellCount(cellCount), cellSize(cellSize),
    offset(offset), windowSize(cellCount*cellSize + 2*offset) {}

void Board::Draw(Color color1, Color color2)
{
  ClearBackground(color1);
  for (int i = 0; i < cellCount; i++)
  {
    for (int j = 0; j < cellCount; j++)
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

void Board::DrawFrame(int thickness, Color color)
{
  DrawRectangleLinesEx(
    (Rectangle){
      offset - thickness,
      offset - thickness,
      cellCount * cellSize + 2 * thickness,
      cellCount * cellSize + 2 * thickness},
    thickness, color
  );
}

void Board::DrawTitle(int fontSize, Color color)
{
  const char* title = "Retro Snake";
  const int width = MeasureText(title, fontSize);
  DrawText(
    title,
    (windowSize - width) / 2,
    (offset - fontSize) / 2,
    fontSize, color
  );
}

void Board::DrawPauseScreen(int fontSize, Color color)
{
  const char* text = "Press 'space' to start";
  const int width = MeasureText(text, fontSize);
  DrawText(
    text,
    (2*offset + cellSize*cellCount - width) / 2,
    (2*offset + cellSize*cellCount - fontSize) / 2,
    fontSize, color
  );
}

void Board::DrawScore(int fontSize, Color color, int score, int thickness)
{
  const char* text = TextFormat("Score: %i", score);
  const int width = MeasureText(text, fontSize);
  DrawText(
    text,
    offset,
    offset + cellSize*cellCount + 2*thickness,
    fontSize,
    color
  );
}

Vector2 Board::GetRandomCell()
{
  return {
    (float)GetRandomValue(0, cellCount - 1),
    (float)GetRandomValue(0, cellCount - 1)
  };
}

Vector2 Board::ToGrid(Vector2 pos)
{
  return {
    pos.x * cellSize + offset,
    pos.y * cellSize + offset
  };
}