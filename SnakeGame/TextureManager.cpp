#include "TextureManager.h"

std::unordered_map<std::string, Texture2D>
  TextureManager::textures;

void TextureManager::Load(
  const std::string& name, 
  const std::string& path
) {
  textures[name] = LoadTexture(path.c_str());
}

Texture2D TextureManager::Get(const std::string& name)
{
  return textures.at(name);
}

void TextureManager::UnloadAll()
{
  for (auto& pair : textures)
  {
    UnloadTexture(pair.second);
  }
}