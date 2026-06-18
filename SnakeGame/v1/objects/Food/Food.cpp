
#include "Food.h"

Food::Food() :Food({0, 0}, {0}) {}
Food::Food(Vector2 pos, Texture2D sprite)
: pos(pos), sprite(sprite) {}
Food::Food(int cellCount, Texture2D sprite)
  : pos(generateRandomPos(cellCount)), sprite(sprite) {}


void Food::Draw(float cellSize) const
{
  float posX = pos.x * cellSize;
  float posY = pos.y * cellSize;

  DrawTexturePro(
    sprite,
    (Rectangle) {0, 0, sprite.width, sprite.height},
    (Rectangle) {posX, posY, cellSize, cellSize},
    (Vector2) {0, 0},
    0.0f,
    WHITE
  );
}

Vector2 Food::generateRandomPos(int cellCount)
{
  float x = GetRandomValue(0, cellCount - 1);
  float y = GetRandomValue(0, cellCount - 1);
  return Vector2{x, y};
}