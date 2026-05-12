#include "Game.h"

Game::Game(Board& board, Music music)
: board(board),
  snake(board),
  food(board, 
    TextureManager::Get(TextureName::Apple),
    GetFoodPosition()
  ), running(false),
  eat(LoadSound("assets/eat.wav")),
  music(music), started(false) {}

void Game::Play() { started = true; }
bool Game::Started() { return started; }
  
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
void Game::SwitchPause()
{
  running = !running;
  if (running) ResumeMusicStream(music);
  else PauseMusicStream(music);
}
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
    PlaySound(eat);
    score++;
  }
}

void Game::GameOver()
{
  food.SetRandomPos();
  snake.Reset();
  running = false;
  score = 0;
  started = false;
  StopMusicStream(music);
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