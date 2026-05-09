#include "Game.h"

Game::Game(Board& board)
: board(board),
  snake(board),
  food(board, 
    TextureManager::Get(TextureName::Apple),
    GetFoodPosition()
  ), running(false) {}

void Game::Draw()
{
  food.Draw();
  snake.Draw(snakeGreen);
}

void Game::Update()
{
  snake.Update();
}

bool Game::IsRunning() { return running; }
void Game::SwitchPause() { running = !running; }
int Game::GetScore() { return score; }

Vector2 Game::GetFoodPosition()
{
  Vector2 newPos;
  do {
    newPos = board.GetRandomCell();
  } while (snake.HasInsideBody(newPos));
  return newPos;
}

void Game::ChangeSnakeDirection(Direction direction)
{
  snake.SetDirection(direction);
}

void Game::CheckCollisionWithFood()
{
  if (snake.IsHeadAt(food.GetPos()))
  {
    food.SetPos(GetFoodPosition());
    snake.Eat();
    score++;
  }
}

void Game::GameOver()
{
  food.SetRandomPos();
  snake.Reset();
  running = false;
  score = 0;
}

void Game::CheckCollisionWithBorder()
{
  if (snake.Head().x < 0
    ||snake.Head().x >= board.cellCount
    ||snake.Head().y < 0
    ||snake.Head().y >= board.cellCount
  ) { GameOver(); }
}

void Game::CheckCollisionWithBody()
{
  if (snake.HeadInsideBody())
    GameOver();
}