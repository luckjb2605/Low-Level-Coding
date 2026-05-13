#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "constants.h"

void DrawX_Axis(SDL_Renderer*);
void DrawY_Axis(SDL_Renderer*);
void ComputeCircle(Point(*)[NUM_OF_POINTS], Circle circle);
void DrawTrigCircle(SDL_Renderer*, Point(&points)[NUM_OF_POINTS]);
void UpdateClockHand(ClockHand*, Circle circle);
void DrawClockHand(SDL_Renderer*, Circle, ClockHand*);