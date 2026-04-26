
#include "Food.h"

Food::Food(Vector2 pos, Texture2D sprite)
  : pos(pos), sprite(sprite) {}

Food::Food() :Food({0, 0}, {0}) {}

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