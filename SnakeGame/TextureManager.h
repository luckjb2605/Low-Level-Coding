#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>

class TextureManager
{
  public:
    static void Load(
      const std::string& name, 
      const std::string& path);
    static Texture2D Get(const std::string&name);
    static void UnloadAll();

  private:
    static std::unordered_map<std::string, Texture2D> textures;
};