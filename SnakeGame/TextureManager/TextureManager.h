#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

enum class TextureName
{
  Apple
};

class TextureManager
{
  public:
    static void Load(
      const TextureName name,
      const std::string& path
    );
    static Texture2D* Get(
      TextureName name
    );
    static void UnloadAll();
  private:
    static std::unordered_map
      <TextureName, Texture2D> textures;
};