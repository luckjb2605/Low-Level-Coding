#include "Food/Food.h"

Food::Food(Board& board, const Texture2D* sprite)
  : board(board), sprite(sprite) {SetRandomPos();}
Food::Food(Board& board, const Texture2D* sprite, Vector2 pos)
  : board(board), sprite(sprite) {SetPos(pos);}

void Food::SetRandomPos() { SetPos(board.GetRandomCell()); }
void Food::SetPos(Vector2 pos) { this->pos = pos; }
Vector2 Food::GetPos() { return pos; }

void Food::Draw() { Draw(this->pos); }
void Food::Draw(Vector2 pos)
{
  DrawTexturePro(
    *sprite,
    (Rectangle) {0, 0, (float)sprite->width, (float)sprite->height},
    (Rectangle) {pos.x, pos.y, board.cellSize, board.cellSize},
    (Vector2) {0, 0},
    0.0f,
    WHITE
  );
}