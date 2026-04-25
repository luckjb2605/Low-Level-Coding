#define _USE_MATH_DEFINES
#include "math.h"
#include "raylib.h"

// JANELA
#define WIDTH 900
#define HEIGHT 600

// CORDAS
#define L1 200
#define L2 200
#define LINE_COLOR WHITE
#define LINE_THICKNESS 3

// MASSAS
#define MASS_RADIUS 20

// RASTRO
#define TRACE_COLOR RED
#define TRACE_LEN 100
Vector2 trace[TRACE_LEN];

// VALORES PRA EQUACAO
#define g 1000
float theta1, theta2, theta1_d, theta2_d, m1, m2;

// -------------- PROGRAMA --------------

Vector2 getPendulumEnd(Vector2 startPos, float theta, float length)
{
  return (Vector2) {
    startPos.x + length * sinf(theta),
    startPos.y + length * cosf(theta)
  };
}

void drawPendulum(Vector2 startPos, Vector2 endPos)
{
  DrawLineEx(startPos, endPos, LINE_THICKNESS, LINE_COLOR);
  DrawCircleV(endPos, MASS_RADIUS, RED);
}

// Circular Buffer
int traceIndex = 0;
int traceCount = 0;
const int TRACE_THICKNESS = 3;
Color color = TRACE_COLOR;
void drawTrace(Vector2 pos)
{
  trace[traceIndex] = pos;
  traceIndex = (traceIndex + 1) % TRACE_LEN;
  if (traceCount < TRACE_LEN) traceCount++; 

  /**
   * Esse loop colore do mais novo ao mais velho.
   * Quando i = 0, alpha = 1
   * e idx1 = traceIndex - 1 (último trace)
   * o + TRACE_LEN está lá apenas para o idx ñ ser negativo.
   * 
   * O "-i" está voltando, percebe?
   * Ou seja, alpha vai do máximo pro mínimo
   * Enquanto idx vai do mais recente pro mais antigo
   */
  for (int i = 0; i < traceCount; i++)
  {
    int idx1 = (traceIndex - 1 - i + TRACE_LEN) % TRACE_LEN;
    int idx2 = (traceIndex - 2 - i + TRACE_LEN) % TRACE_LEN;

    float alpha = (float) i / traceCount;
    color.a = 0xFF * (1.0f - alpha);

    DrawLineEx(trace[idx1], trace[idx2], TRACE_THICKNESS, color);
  }
}

void drawDoublePendulum(Vector2 startPos, float theta1, float theta2)
{
  Vector2 mass1Pos = getPendulumEnd(startPos, theta1, L1);
  Vector2 mass2Pos = getPendulumEnd(mass1Pos, theta2, L2);

  // Desenha o segundo primeiro pra linha nao ficar em cima.
  drawPendulum(mass1Pos, mass2Pos); // Segundo
  drawPendulum(startPos, mass1Pos); // Primeiro

  drawTrace(mass2Pos);
}

void step(float dt)
{
  // aceleração angular
  float theta1_dd = (
    (-g*(2*m1+m2)*sinf(theta1)) - (m2*g*sinf(theta1-2*theta2)) - 
    (2*sinf(theta1-theta2)*m2*(theta2_d*theta2_d*L2+theta1_d*theta1_d*L1*cosf(theta1-theta2)))
    ) / ( 
    L1*(2*m1+m2-m2*cosf(2*theta1-2*theta2))
  );

  float theta2_dd = (
    (2*sinf(theta1-theta2))*((theta1_d*theta1_d*L1*(m1+m2)) +
    (g*(m1+m2)*cosf(theta1)) + (theta2_d*theta2_d*L2*m2*cosf(theta1-theta2)))
    ) / (
    L2*(2*m1+m2-m2*cosf(2*theta1-2*theta2))
  );

  // velocidade angular
  theta1_d += theta1_dd * dt;
  theta2_d += theta2_dd * dt;

  // proprio angulo
  theta1 += theta1_d * dt;
  theta2 += theta2_d * dt;
}

void initSolver()
{
  theta1 = GetRandomValue(-90,90)*DEG2RAD;
  theta2 = GetRandomValue(-90,90)*DEG2RAD;
  theta1_d = 0;
  theta2_d = 0;
  m1 = 1;
  m2 = 1;
}

int main(void)
{
  InitWindow(WIDTH, HEIGHT, "Double Pendulum");
  SetTargetFPS(60);

  Vector2 start_pos = (Vector2) {WIDTH/2, 0};

  initSolver();

  while(!WindowShouldClose())
  {
    step(GetFrameTime());

    if (IsKeyPressed(KEY_SPACE))
    {
      initSolver();
      traceIndex = 0;
      traceCount = 0;
    }

    BeginDrawing();
      ClearBackground(BLACK);
      drawDoublePendulum(start_pos, theta1, theta2);
    EndDrawing();
  }

  return 0;
}