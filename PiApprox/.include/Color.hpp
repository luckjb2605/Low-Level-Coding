#pragma once
#include <SDL2/SDL.h>

struct Color
{
  Uint8 r,g,b,a;
};

inline constexpr Color BLACK = {0x00,0x00,0x00,0xFF};
inline constexpr Color WHITE = {0xFF,0xFF,0xFF,0xFF};