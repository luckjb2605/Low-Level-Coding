#pragma once
#include <raylib.h>

class Food
{
  public:
    Food();
    Food(Vector2 pos, Texture2D sprite);
    Food(int cellCount, Texture2D sprite);
    void Draw(float cellSize) const;
  private:
    Vector2 pos;
    Texture2D sprite;
    Vector2 generateRandomPos(int cellCount);
};