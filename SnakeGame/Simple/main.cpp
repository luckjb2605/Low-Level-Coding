#include <raylib.h>
#include <raymath.h>
#include <deque>

#include <stdio.h>
#include <iostream>

const int cellCount = 15;
const float cellSize = 30;
const int offset = cellSize * 2;
const int frameThickness = cellSize / 4;
const float windowSize = cellCount * cellSize + 2 * offset;

const float textSize = windowSize / 20;
const float titleSize = offset * 2 / 3;
const float scoreSize = offset * 1 / 2;

const Color snakeGreen = {43, 51, 24, 255};
const Color darkGreen = {76, 175, 80, 255};
const Color greenBackground = {139, 195, 74, 255};
const Color appleRed = {255, 0, 0, 255};

bool running = false;
const float snakeRefreshTime = 0.2;
int score = 0;

void DrawTitle()
{
  const char* title = "Retro Snake";
  int textWidth = MeasureText(title, titleSize);
  DrawText(
    title,
    (windowSize - textWidth) / 2,
    (offset - titleSize) / 2,
    titleSize, snakeGreen
  );
}

void DrawScore()
{
  const char* scoreText = TextFormat("Score: %d", score);
  int textWidth = MeasureText(scoreText, scoreSize);
  DrawText(
    scoreText, offset,
    offset + cellSize * cellCount 
    + 2 * frameThickness,
    scoreSize, snakeGreen
  );
}

void DrawStartText()
{
  const char* text = "Press 'space' to start!";
  int textWidth = MeasureText(text, textSize);
  DrawText(
    text,
    (windowSize - textWidth) / 2,
    (windowSize - textSize) / 2,
    textSize,
    darkGreen
  );
}

void DrawFrame()
{
  DrawRectangleLinesEx(
    {
      offset - frameThickness,
      offset - frameThickness,
      cellCount * cellSize + 2 * frameThickness,
      cellCount * cellSize + 2 * frameThickness
    },
    frameThickness, snakeGreen
  );
}

class BodyPart
{
  public:
    BodyPart(Vector2 pos)
      : pos(pos) {}
    void Draw()
    {
      DrawRectangleRounded(
        {
          pos.x * cellSize + offset,
          pos.y * cellSize + offset,
          cellSize, cellSize 
        },
        0.5f, 10, snakeGreen
      );
    }
    void UpdatePos(Vector2 direction)
    {
      pos = Vector2Add(pos, direction);
      // if (pos.x < 0)
      //   pos.x = cellCount - 1;
      // if (pos.x >= cellCount)
      //   pos.x = 0;
      // if (pos.y < 0)
      //   pos.y = cellCount - 1;
      // if (pos.y >= cellCount)
      //   pos.y = 0;
    }
  Vector2 pos;
};

const std::deque<BodyPart> startingPos =
{
  {{6, 2}},
  {{5, 2}},
  {{4, 2}},
  {{3, 2}},
  {{2, 2}},
};

class Snake
{
  std::deque<BodyPart> body = startingPos;
  public:
    Vector2 direction;
    bool addingSegment = false;
    Snake() : direction({1,0}) {}
    void Update()
    {
      BodyPart newHead = body[0];
      newHead.UpdatePos(direction);
      body.push_front(newHead);
      if (!addingSegment)
      {
        body.pop_back();
        return;
      }
      addingSegment = false;
    }
    void Draw()
    {
      for (auto part : body)
        part.Draw();
      }
    void Reset()
    {
      body = startingPos;
      direction = {1,0};
      running = false;
    }
    bool CollidedWithApple(Vector2& objectPos)
    {
      return Vector2Equals(body[0].pos, objectPos);
    }
    bool CollidedWithEdge()
    {
      return (
        body[0].pos.x < 0 ||
        body[0].pos.y < 0 ||
        body[0].pos.x >= cellCount ||
        body[0].pos.y >= cellCount
      );
    }
    bool CollidedWithBody()
    {
      std::deque<BodyPart> headlessBody = body;
      headlessBody.pop_front();
      return PosInDeque(body[0].pos, headlessBody);
    }
    bool PosInDeque(Vector2& pos, std::deque<BodyPart>& deque)
    {
      for (auto part : deque)
      {
        if (Vector2Equals(pos, part.pos))
          return true;
      }
      return false;
    }
    bool PosInsideBody(Vector2& pos)
    {
      return PosInDeque(pos, body);
    }
};


class Food
{
  Snake& snake;
  public:
    Vector2 pos;
    Food(Snake& snake)
      : pos(GetRandomCell(snake)),
        snake(snake) {}
    void Draw()
    {
      DrawRectangleRounded(
        {pos.x * cellSize + offset, 
         pos.y * cellSize + offset,
         cellSize, cellSize},
        0.5f, 10, appleRed
      );
    }
    void Reposition()
    {
      pos = GetRandomCell(snake);
    }
    Vector2 GetRandomCell(Snake& snake)
    {
      Vector2 newPos;
      do
      {
        newPos = {
          (float)GetRandomValue(0, cellCount - 1),
          (float)GetRandomValue(0, cellCount - 1)
        };
      } while (snake.PosInsideBody(newPos));
      return newPos;
    }
};

double lastUpdateTime = 0;
bool intervalPassed(double interval)
{
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval)
  {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

int main()
{
  InitWindow(windowSize, windowSize, "SnakeGame");
  SetTargetFPS(60);
  
  std::cout << windowSize / 15 << std::endl;
  std::cout << offset * 2 / 3  << std::endl;


  Snake snake = Snake();
  Food food = Food(snake);

  while(!WindowShouldClose())
  {
    BeginDrawing();
      
      ClearBackground(greenBackground);
      DrawFrame();
      
      DrawTitle();
      DrawScore();

      snake.Draw();
      food.Draw();
      
      if (IsKeyPressed(KEY_SPACE))
        running = !running;
      
      if (!running)
        DrawStartText();

      if (running)
      {
        if (intervalPassed(snakeRefreshTime))
        {
          snake.Update();
          if (snake.CollidedWithApple(food.pos))
          {
            snake.addingSegment = true;
            food.Reposition();
            score++;
          }
          if (snake.CollidedWithEdge() 
           || snake.CollidedWithBody())
          {
            food.Reposition();
            snake.Reset();
            score = 0;
          }
        }
        
        if (IsKeyPressed(KEY_W) && (snake.direction.y != 1)) 
        snake.direction = {0,-1};
        
        if (IsKeyPressed(KEY_A) && (snake.direction.x != 1))
        snake.direction = {-1,0};
        
        if (IsKeyPressed(KEY_S) && (snake.direction.y != -1))
        snake.direction = {0,1};
        
        if (IsKeyPressed(KEY_D) && (snake.direction.x != -1))
        snake.direction = {1,0};
      }
        
    EndDrawing();
  }

  CloseWindow();
  return 0;
}