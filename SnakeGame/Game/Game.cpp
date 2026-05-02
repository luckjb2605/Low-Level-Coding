#include "Game.h"

Game::Game(Board& board)
: snake(board, {{6,9}, {5, 9}, {4, 9}}),
food(board, TextureManager::Get(TextureName::Apple)){}

void Game::Draw()
{
  food.Draw();
  snake.Draw(snakeGreen);
}

void Game::Update()
{
  snake.Update();
}

void Game::ChangeSnakeDirection(Direction direction)
{
  snake.SetDirection(direction);
}

void Game::CheckCollisionWithFood()
{
  // TODO: Not pop + check is not working currently for unknown reason
  if (snake.IsHeadAt(food.GetPos()))
  {
    food.SetRandomPos();
  }
}