#pragma once
#include <SDL2/SDL.h>
#include "Vector2.hpp"

struct Box
{
  int size;
  float mass;
  Vector2 pos, vel, acc;

  void Update()
  {
    vel += acc;
    pos += vel;
  }
};