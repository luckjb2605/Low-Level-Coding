#include "TextureManager/TextureManager.h"

std::unordered_map<TextureName, Texture2D> 
  TextureManager::textures;

void TextureManager::Load(
  const TextureName name,
  const std::string& path
) {
  textures[name] = LoadTexture(path.c_str());
}

Texture2D* TextureManager::Get(TextureName name)
{
  return &textures.at(name);
}

void TextureManager::UnloadAll()
{
  for (auto& pair : textures)
  {
    UnloadTexture(pair.second);
  }
}