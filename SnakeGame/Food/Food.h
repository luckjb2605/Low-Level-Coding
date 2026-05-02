#pragma once
#include <raylib.h>

#include "Board/Board.h"

class Food
{
  public:
    Food(Board& board, const Texture2D* sprite);
    Food(Board& board, const Texture2D* sprite, Vector2 pos);
    
    void SetRandomPos();
    void SetPos(Vector2 pos);
    Vector2 GetPos();

    void Draw();
    void Draw(Vector2 pos);

  private:
    const Texture2D* sprite;
    Board& board;
    Vector2 pos;
};