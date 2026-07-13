#pragma once

struct Vector2
{
  float x = 0.0f;
  float y = 0.0f;

  Vector2 operator+(const Vector2 other)
  {
    return {
      x + other.x,
      y + other.y
    };
  }

  Vector2 operator-(const Vector2 other)
  {
    return {
      x - other.x,
      y - other.y
    };
  }

  Vector2 operator*(float scalar)
  {
    return {
      x * scalar,
      y * scalar
    };
  }

  Vector2& operator+=(const Vector2 other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2& operator-=(const Vector2 other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }
};