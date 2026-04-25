#include "raylib.h"

int main()
{
  float windowWidth = 800;
  float windowHeight = 450;

  // Inicializando a sprite antes da criação da janela
  Texture2D sonicSprite;
  Texture2D background;
  Sound sound;
  Music music;

  InitWindow(windowWidth, windowHeight, "Vida longa a Velocidade da Luz");
  InitAudioDevice();

  // Carregando a sprite apos a criacao da janela
  sonicSprite = LoadTexture("Raylib Test/assets/sonic.png");
  background = LoadTexture("Raylib Test/assets/background.png");
  sound = LoadSound("Raylib Test/assets/gunshot.mp3");
  music = LoadMusicStream("Raylib Test/assets/music.mp3");

  // Apos carregar a textura, pode se acessar suas propriedades para uso:
  float posX = -sonicSprite.width;
  float posY = (windowHeight - sonicSprite.height) / 2.0f;

  while (!WindowShouldClose())
  {
    UpdateMusicStream(music);

    posX += GetFrameTime() * 250;
    
    if (posX >= windowWidth)
    {
      posX = -sonicSprite.width;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      Rectangle spriteRec = {
        posX,
        posY,
        sonicSprite.width,
        sonicSprite.height
      };

      if (CheckCollisionPointRec(GetMousePosition(), spriteRec))
      {
        PlaySound(sound); // Multi pra tocar mais de um som por vez
      }
    }

    if (IsKeyPressed(KEY_SPACE))
    {
      StopMusicStream(music);
      PlayMusicStream(music);
    }
    
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawTexturePro(
        background, // Imagem (Textura)
        (Rectangle) {0, 0, background.width, background.height}, // Seleciona a imagem inteira
        (Rectangle) {0, 0, 800, 450}, // Formato de Destino
        (Vector2) {0, 0}, // Origem pra rotacao e translacao
        0.0f, // Rotacao
        WHITE // White = Sem filtro de cor
      );

      DrawTexture(sonicSprite, posX, posY, WHITE);

    EndDrawing();
  }

  StopMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}