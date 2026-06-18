#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>

enum class TextureName
{
  Apple,
  SnakeHead,
  SnakeBody,
  SnakeCurve,
  SnakeTail,
};

class TextureManager
{
  public:
    static void Load(
      const TextureName name, 
      const std::string& path);
    static Texture2D Get(const TextureName name);
    static void UnloadAll();

  private:
    static std::unordered_map<TextureName, Texture2D> textures;
};